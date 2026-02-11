g2_move(int dev, double x, double y)
{
    g2_device *devp;
    int i;

    if((devp=g2_get_device_pointer(dev))==NULL) {
	fprintf(stderr, "g2_move: No such device: %d\n", dev);
	return;
    }

    devp->x=x;
    devp->y=y;

    switch(devp->t) {
      case g2_PD:
	break;
      case g2_VD:
	for(i=0;i<devp->d.vd->N;i++)
	    g2_move(devp->d.vd->dix[i], x, y);
	break;
      case g2_ILLEGAL:
	break;
      case g2_NDEV:
	break;
    }
    __g2_last_device=dev;
}
