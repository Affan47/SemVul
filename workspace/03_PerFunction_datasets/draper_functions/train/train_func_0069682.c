g2_poly_line(int dev, int N_pt, double *points)
{
    g2_device *devp;
    int i;

    if((devp=g2_get_device_pointer(dev))==NULL) {
	fprintf(stderr, "g2_poly_line: No such device: %d\n", dev);
	return;
    }

    devp->x=points[2*(N_pt-1)+0];
    devp->y=points[2*(N_pt-1)+1];

    switch(devp->t) {
      case g2_PD:
	g2_poly_line_pd(devp->d.pd, N_pt, points);
	break;
      case g2_VD:
	for(i=0;i<devp->d.vd->N;i++)
	    g2_poly_line(devp->d.vd->dix[i], N_pt, points);
	break;
      case g2_ILLEGAL:
	break;
      case g2_NDEV:
	break;
    }

    if(devp->auto_flush)
	g2_flush(dev);

    __g2_last_device=dev;
}
