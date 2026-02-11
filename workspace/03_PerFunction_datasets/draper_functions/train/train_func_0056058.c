map_gen_spiral(int xsize, int ysize, int option) {
    int i, j;
    float parm = 0;
    float x = 0, y = 0;
    int ic, jc;
    float SizeX, SizeY;
    float xscale, yscale;


    char **maze = (char **)calloc(sizeof(char *), xsize);

    for (i = 0; i < xsize; i++) {
        maze[i] = (char *)calloc(sizeof(char), ysize);
    }


    for (i = 0; i < xsize; i++)
        for (j = 0; j < ysize; j++)
            maze[i][j] = '#';

    ic = xsize/2;
    jc = ysize/2;
    SizeX = xsize/2-2;
    SizeY = ysize/2-2;


    if (option == 0) {
        option = RANDOM()%MAX_SPIRAL_OPT;
    }


    if ((option&REGULAR_SPIRAL) && (option&FIT_SPIRAL)) {

        if (RANDOM()%2 && (option&REGULAR_SPIRAL))
            option -= REGULAR_SPIRAL;
        else
            option -= FIT_SPIRAL;
    }

    xscale = yscale = MAX_FINE;


    if (!(option&FINE_SPIRAL)) {
        float pitch = (RANDOM()%5)/10.+10./22.;

        xscale = yscale = pitch;
    }

    if ((option&FIT_SPIRAL) && (xsize != ysize)) {
        if (xsize > ysize)
            xscale *= (float)xsize/(float)ysize;
        else
            yscale *= (float)ysize/(float)xsize;
    }

    if (option&REGULAR_SPIRAL) {
        float scale = MIN(xscale, yscale);

        xscale = yscale = scale;
    }


    while ((abs(x) < SizeX) && (abs(y) < SizeY)) {
        x = parm*cos(parm)*xscale;
        y = parm*sin(parm)*yscale;
        maze[(int)(ic+x)][(int)(jc+y)] = '\0';
        parm += 0.01;
    };

    maze[(int)(ic+x+0.5)][(int)(jc+y+0.5)] = '<';


    maze[ic][jc+1] = '>';
    maze[ic][jc] = 'C';

    return maze;
}
