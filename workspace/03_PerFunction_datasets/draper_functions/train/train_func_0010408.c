g2_arc_pd(g2_physical_device *pd,
	       double x, double y, double r1, double r2, double a1, double a2)
{
    int    ix, iy, ir1, ir2;
    double dx, dy, dr1, dr2;

    if(pd->ff[g2_Arc].fun!=NULL) {
	switch(pd->coor_type) {
	  case g2_IntCoor:
	    g2_uc2pdc_int(pd, x, y, &ix, &iy);
	    g2_us2pds_int(pd, r1, r2, &ir1, &ir2);
	    pd->ff[g2_Arc].fun(pd->pid, pd->pdp,
			       ix, iy, ir1, ir2, a1, a2);
	    break;
	  case g2_DoubleCoor:
	    g2_uc2pdc_double(pd, x, y, &dx, &dy);
	    g2_us2pds_double(pd, r1, r2, &dr1, &dr2);
	    pd->ff[g2_Arc].fun(pd->pid, pd->pdp,
			       dx, dy, dr1, dr2, a1, a2);
	    break;
	}
    } else {
	double a, da, *pt;
	int N, i;
	N=(a2==a1)?360:(int)fabs(a2-a1)+8;
	a=a1*2.*PI/360.;
	da=((a2>a1)? (a2-a1):360.-(a1-a2))*2.*PI/360./(N-1);
	pt=g2_malloc(2*N*sizeof(double));
	for(i=0;i<N;i++) {
	    pt[2*i+0]=x+r1*cos(a+i*da);
	    pt[2*i+1]=y+r2*sin(a+i*da);
	}
	g2_poly_line_pd(pd, N, pt);
	g2_free(pt);
    }
}
