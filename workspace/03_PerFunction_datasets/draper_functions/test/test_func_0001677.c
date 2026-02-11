plD_init_xfig(PLStream *pls)
{
    PLDev *dev;

    plParseDrvOpts(xfig_options);
    if (text)
      pls->dev_text = 1;


    plFamInit(pls);


    plOpenFile(pls);


    dev = plAllocDev(pls);

    dev->xold = PL_UNDEFINED;
    dev->yold = PL_UNDEFINED;
    dev->xmin = 0;
    dev->xmax = FIGX;
    dev->ymin = 0;
    dev->ymax = FIGY;
    dev->xscale_dev = DPI/25.4;
    dev->yscale_dev = DPI/25.4;
    offset_inc = dev->ymax * (PLINT)dev->yscale_dev;
    offset = - offset_inc;
    pls->dev_fill0 = 1;
    if (!pls->colorset)
      pls->color = 1;

    plP_setpxl(dev->xscale_dev, dev->xscale_dev);
    plP_setphy(0, FIGX * dev->xscale_dev, 0, FIGY * dev->yscale_dev);


    fprintf(pls->OutFile, "#FIG 3.2\n");
    fprintf(pls->OutFile, "Landscape\n");
    fprintf(pls->OutFile, "Center\n");
    fprintf(pls->OutFile, "Metric\n");
    fprintf(pls->OutFile, "A4\n");
    fprintf(pls->OutFile, "100.0\n");
    fprintf(pls->OutFile, "Single\n");
    fprintf(pls->OutFile, "-2\n");
    fprintf(pls->OutFile, "%d 2\n", DPI);


    cmap0_ncol = 2 * pls->ncol0;
    cmap0_pos = ftell(pls->OutFile);
    stcmap0(pls);


    cmap1_ncol = 2 * pls->ncol1;
    cmap1_pos = ftell(pls->OutFile);
    stcmap1(pls);

    bufflen = 2 * BSIZE;
    buffptr = (short *) malloc(sizeof(short) * bufflen);
    if (buffptr == NULL)
	plexit("Out of memory!");
}
