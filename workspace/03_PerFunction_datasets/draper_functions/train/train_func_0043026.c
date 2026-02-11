c_plclear(void)
{
    if (plsc->level < 1) {
	plabort("plclear: Please call plinit first");
	return;
    }

    if (plsc->dev_clear)
      plP_esc(PLESC_CLEAR, NULL);
    else {

	  short x[5], y[5];
	  int ocolor = plsc->icol0;

	  x[0] = x[3] = x[4] = plsc->sppxmi;
	  x[1] = x[2] = plsc->sppxma;
	  y[0] = y[1] = y[4] = plsc->sppymi;
	  y[2] = y[3] = plsc->sppyma;
	  plcol0(0);
	  plP_fill(x, y, 5);
	  plcol0(ocolor);
    }
}
