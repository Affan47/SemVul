pixelexp16signed(short *pixels, unsigned long rows,
		 unsigned long cols, unsigned long factor,
	     short **pixout, unsigned long *newRows, unsigned long *newCols)
{
    unsigned long
        i,
        j,
        k,
        l,
        bigi;
    short
       *p,
        t;
    unsigned long
        r,
        c;

    r = rows * factor;
    c = cols * factor;

    p = malloc(r * c * sizeof(short));
    if (p == NULL)
	return (short) 0;

    *pixout = p;
    for (i = 0; i < rows; i++) {
	for (j = 0; j < cols; j++) {
	    t = *(pixels + (i * cols) + j);

	    bigi = ((i * factor) * c) + (j * factor);
	    for (k = bigi; k < (bigi + factor); k++) {
		for (l = 0; l < factor; l++) {
		    p[k + (l * c)] = t;
		}
	    }
	}
    }
    *newRows = rows * factor;
    *newCols = cols * factor;
    return (short) 1;
}
