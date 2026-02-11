creators_points (int radius, int x1, int y1, int color1)
{
    int             z, x, y, x2, y2;
    double r;
    int             time = 50;
    int             midX, midY, r2,r1;

    midX = GAMEWIDTH / 2;
    midY = GAMEHEIGHT / 2;
    r2 = r1 = MIN(midX, midY);
    r2 *= r2;

    z = radius * radius * M_PI / DIV / DIV;
    while (z--) {
	do {
	    x = rand() % GAMEWIDTH;
	    y = rand() % GAMEHEIGHT;
	} while (((x-midX)*(x-midX) + (y-midY)*(y-midY)) > r2);
	r=sqrt((double)((x-midX)*(x-midX) + (y-midY)*(y-midY)));
	r=(r*radius/r1)/r*0.9;
	x2=x1+(x-midX)*r;
	y2=y1+(y-midY)*r;

	addpoint(x * 256, y * 256,
		    (x2 - x) * 256 / (time),
		    (y2 - y) * 256 / (time),
		    color1 + (rand() % (DIV == 1 ? 16 : 32)),
		    time);
    }
}
