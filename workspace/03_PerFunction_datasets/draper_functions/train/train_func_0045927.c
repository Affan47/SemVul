ajRandomDouble(void)
{
    static double offset = 1.0/AjRandomYmod;
    static double xmod2  = 2.0*AjRandomXmod;
    static double xmod4  = 4.0*AjRandomXmod;

    ajint n;
    double x, y;


    if(!aj_rand_i)
	ajRandomSeed();


    if((n = aj_rand_index-64) < 0)
	n += 101;

    x = aj_rand_poly[aj_rand_index]+aj_rand_poly[aj_rand_index];
    x = xmod4-aj_rand_poly[n]-aj_rand_poly[n]-x-x-aj_rand_poly[aj_rand_index];

    if(x <= 0.0)
    {
        if(x < -AjRandomXmod)
	    x += xmod2;

        if(x < 0.0)
	    x += AjRandomXmod;
    }
    else
    {
        if(x >= xmod2)
	{
            x = x-xmod2;

            if(x >= AjRandomXmod)
		x -= AjRandomXmod;
        }

        if(x >= AjRandomXmod)
	    x -= AjRandomXmod;
    }

    aj_rand_poly[aj_rand_index] = x;

    if(++aj_rand_index >= 101)
	aj_rand_index = 0;


    do
    {
        y = 37.0*aj_rand_other+offset;
        aj_rand_other = y-floor(y);
    }
    while(E_FPZERO(aj_rand_other,U_DEPS));

    if((x = x/AjRandomXmod+aj_rand_other) >= 1.0)
	x -= 1.0;


    return x+AjRandomTiny;
}
