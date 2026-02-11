plD_bop_hpgl(PLStream *pls)
{
    PLDev *dev = (PLDev *) pls->dev;

    dev->xold = PL_UNDEFINED;
    dev->yold = PL_UNDEFINED;

    fputs( "PG;\n", OF );
    if (!pls->termin)
	plGetFam(pls);

    pls->page++;
}
