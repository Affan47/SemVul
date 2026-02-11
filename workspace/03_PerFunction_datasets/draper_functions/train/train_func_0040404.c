g2_image(int dev, double x, double y, int x_size, int y_size, int *pens)
{
    g2_device *devp;
    int i;

    if((devp=g2_get_device_pointer(dev))==NULL) {
	fprintf(stderr, "g2_image: No such device: %d\n", dev);
	return;
    }

    devp->x=x;
    devp->y=y;

    switch(devp->t) {
      case g2_PD:
	g2_image_pd(devp->d.pd, x, y, x_size, y_size, pens);
	break;
      case g2_VD:
	for(i=0;i<devp->d.vd->N;i++)
	    g2_image(devp->d.vd->dix[i], x, y, x_size, y_size, pens);
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
