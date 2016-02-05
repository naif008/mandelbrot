#include <stdio.h>
#include <assert.h>

#define HEIGHT 30
#define WIDTH 72
#define MANDELBROT_X_START -1.5
#define MANDELBROT_Y_START 1
#define MANDELBROT_X_END 1
#define MANDELBROT_Y_END -1
#define X_RANGE 2.5
#define Y_RANGE -2
#define ZOOM_LEVEL 3

// view port:

typedef struct {
	double x;
	double y;
} point;

int mandelbrot(double x, double y);
void square(point * p);
double lengthSquared(point * p);
void transform(double * x, double * y);
void tests();
void setPoint(point * p, double x, double y);
void addPoint(point * p, point * q);

int main()
{
//	tests();
	int x = 0;
	int y = 0;

	while( y < HEIGHT) 
	{
		while ( x < WIDTH)
		{
			if(mandelbrot(x, y))
			{
				printf("*");
			}
			else
			{
				printf(" ");
			}
			x++;
		}
		printf("\n");
		x = 0;
		y++;
	}
	return 0;
}


// transform view coordinate to mandelbrot coordinate
void transform(double * x, double * y)
{
	*x = *x / WIDTH * X_RANGE + MANDELBROT_X_START;
	*y = *y / HEIGHT * Y_RANGE + MANDELBROT_Y_START;
}

int mandelbrot(double x, double y)
{
	transform(&x, &y);
	point p;
	setPoint(&p, x,y);
	int counter = 0;
	double result = 0;
	while(counter < 255)
	{
		square(&p);
		p.x += x;
		p.y += y;
		result = lengthSquared(&p);
		if(result >= 4.0)
		{
			return 0;
		}
		else
		{
		counter++;
		}
	}
	return 1;
}

void square(point * p)
{
	double x = p->x;
	double y = p->y;
	p->x = (p->x * p->x) - (p->y * p->y);
	p->y = 2 * x * y;
}
// compute the length/magnitude (squared) of a 2D vector
// in other words the distance squared of a point from the origin.
double lengthSquared(point * p)
{
	assert(p != NULL);
	return (p->x * p->x) + (p->y * p->y);
}
void setPoint(point * p, double x, double y)
{
	assert(p != NULL);
	p->x = x;
	p->y = y;
}
void addPoint(point * p, point * q)
{
	p->x += q->x;
	p->y += q->y;
}
