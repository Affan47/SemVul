g2_triangle_pd(g2_physical_device *pd,
		    double x1, double y1,
		    double x2, double y2,
		    double x3, double y3)
{
    int    ix1, iy1, ix2, iy2, ix3, iy3;
    double dx1, dy1, dx2, dy2, dx3, dy3;

    if(pd->ff[g2_Triangle].fun!=NULL) {
	switch(pd->coor_type) {
	  case g2_IntCoor:
	    g2_uc2pdc_int(pd, x1, y1, &ix1, &iy1);
	    g2_uc2pdc_int(pd, x2, y2, &ix2, &iy2);
	    g2_uc2pdc_int(pd, x3, y3, &ix3, &iy3);
	    pd->ff[g2_Triangle].fun(pd->pid, pd->pdp,
				    ix1, iy1,
				    ix2, iy2,
				    ix3, iy3);
	    break;
	  case g2_DoubleCoor:
	    g2_uc2pdc_double(pd, x1, y1, &dx1, &dy1);
	    g2_uc2pdc_double(pd, x2, y2, &dx2, &dy2);
	    g2_uc2pdc_double(pd, x3, y3, &dx3, &dy3);
	    pd->ff[g2_Triangle].fun(pd->pid, pd->pdp,
				    dx1, dy1,
				    dx2, dy2,
				    dx3, dy3);
	}
    } else {
	g2_line_pd(pd, x1, y1, x2, y2);
	g2_line_pd(pd, x2, y2, x3, y3);
	g2_line_pd(pd, x3, y3, x1, y1);
    }
}
