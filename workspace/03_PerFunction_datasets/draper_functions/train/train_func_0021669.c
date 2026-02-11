c_plsvect(PLFLT *arrowx, PLFLT *arrowy, PLINT npts, PLINT fill) {
    int i;

    if (plsc->arrow_x) free_mem(plsc->arrow_x);
    if (plsc->arrow_y) free_mem(plsc->arrow_y);

    plsc->arrow_x = (PLFLT *)malloc(npts*sizeof(PLFLT));
    plsc->arrow_y = (PLFLT *)malloc(npts*sizeof(PLFLT));

    plsc->arrow_npts = npts;
    plsc->arrow_fill = fill;
    for (i=0; i<npts; i++) {
      plsc->arrow_x[i] = arrowx[i];
      plsc->arrow_y[i] = arrowy[i];
    }
}
