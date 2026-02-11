g2_query_pointer(int dev, double *x, double *y, unsigned int *button)
{
    g2_device *devp;

    if((devp=g2_get_device_pointer(dev))==NULL) {
	fprintf(stderr, "g2_query_pointer: No such device: %d\n", dev);
	return;
    }

    switch(devp->t) {
      case g2_PD:
	g2_query_pointer_pd(devp->d.pd, x, y, button);
	break;
      case g2_VD:
	break;
      case g2_ILLEGAL:
	break;
      case g2_NDEV:
	break;
    }
    __g2_last_device=dev;
}
