c_plcpstrm(PLINT iplsr, PLINT flags)
{
    int i;
    PLStream *plsr;

    plsr = pls[iplsr];
    if (plsr == NULL) {
	fprintf(stderr, "plcpstrm: stream %d not in use\n", (int) iplsr);
	return;
    }


    plsc->debug = plsr->debug;


#ifdef BUFFERED_FILE
    plsc->plbufFile = plsr->plbufFile;
#else
    plsc->plbuf_buffer = plsr->plbuf_buffer;
    plsc->plbuf_buffer_grow = plsr->plbuf_buffer_grow;
    plsc->plbuf_buffer_size = plsr->plbuf_buffer_size;
    plsc->plbuf_top = plsr->plbuf_top;
    plsc->plbuf_readpos = plsr->plbuf_readpos;
#endif


    if (plsr->difilt & PLDI_PLT)
	plsdiplt(plsr->dipxmin, plsr->dipymin, plsr->dipxmax, plsr->dipymax);

    if (plsr->difilt & PLDI_DEV)
	plsdidev(plsr->mar, plsr->aspect, plsr->jx, plsr->jy);

    if (plsr->difilt & PLDI_ORI)
	plsdiori(plsr->diorot);


    if ( ! (flags & 0x01)) {
	pldebug("plcpstrm", "mapping parameters: %d %d %d %d %f %f\n",
		plsr->phyxmi, plsr->phyxma, plsr->phyymi, plsr->phyyma,
		plsr->xpmm, plsr->ypmm);
	plsdimap(plsr->phyxmi, plsr->phyxma, plsr->phyymi, plsr->phyyma,
		 plsr->xpmm, plsr->ypmm);
    }


    pl_cpcolor(&plsc->curcolor, &plsr->curcolor);


    plsc->icol0 = plsr->icol0;
    plsc->ncol0 = plsr->ncol0;
    if (plsc->cmap0 != NULL)
	free((void *) plsc->cmap0);

    plsc->cmap0 = (PLColor *) calloc(1, plsc->ncol0 * sizeof(PLColor));
    for (i = 0; i < plsc->ncol0; i++)
	pl_cpcolor(&plsc->cmap0[i], &plsr->cmap0[i]);


    plsc->icol1 = plsr->icol1;
    plsc->ncol1 = plsr->ncol1;
    if (plsc->cmap1 != NULL)
	free((void *) plsc->cmap1);

    plsc->cmap1 = (PLColor *) calloc(1, plsc->ncol1 * sizeof(PLColor));
    for (i = 0; i < plsc->ncol1; i++)
	pl_cpcolor(&plsc->cmap1[i], &plsr->cmap1[i]);


    if (plsc->level == 0)
	plinit();
}
