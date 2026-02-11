ajGraphicsDrawsetLines(ajuint num, PLFLT *xx, PLFLT *yy,
                            PLFLT *xx2, PLFLT *yy2)
{
    ajuint i = 0;
    PLFLT *xa = xx;
    PLFLT *ya = yy;
    PLFLT *xb = xx2;
    PLFLT *yb = yy2;


    for(i=0; i<num; i++)
	ajGraphicsDrawposLine(*xa++,*ya++,*xb++,*yb++);

    return;
}
