plhrsh2(PLINT ch, PLINT x, PLINT y)
{
    PLINT cx, cy, k, penup, style;
    signed char *vxygrid = 0;
    PLFLT scale, xscale, yscale;
    PLINT llx[STLEN], lly[STLEN], l = 0;

    penup = 1;
    scale = 0.05 * plsc->symht;

    if ( ! plcvec(ch, &vxygrid)) {
	plP_movphy(x, y);
	return;
    }


    style = plsc->nms;
    plsc->nms = 0;


    xscale = scale * plsc->xpmm;
    yscale = scale * plsc->ypmm;

    k = 4;
    for (;;) {
	cx = vxygrid[k++];
	cy = vxygrid[k++];
	if (cx == 64 && cy == 64) {
	  if (l) {
	    plP_draphy_poly(llx, lly, l);
	    l = 0;
	  }
	  plP_movphy(x, y);
	  plsc->nms = style;
	  return;
	}
	else if (cx == 64 && cy == 0)
	    penup = 1;
	else {
	    if (penup == 1) {
             if (l) {
	       plP_draphy_poly(llx, lly, l);
	       l = 0;
	     }
             llx[l] = ROUND(x+ xscale * cx);
	     lly[l++] = ROUND(y + yscale * cy);
             plP_movphy(llx[l-1], lly[l-1]);
	     penup = 0;
	    }
	    else {
	      llx[l] = ROUND(x+ xscale * cx);
	      lly[l++] = ROUND(y + yscale * cy);
	    }
	}
    }
}
