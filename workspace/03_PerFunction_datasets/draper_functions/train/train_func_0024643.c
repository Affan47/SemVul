g2_ink(int pd_dev, double red, double green, double blue)
{
    g2_device *devp;
    int rv=-1;

    if((devp=g2_get_device_pointer(pd_dev))==NULL) {
	fprintf(stderr, "g2_ink: No such device: %d\n", pd_dev);
	return -1;
    }

    if(red   < 0.0) red=0.0;
    if(green < 0.0) green=0.0;
    if(blue  < 0.0) blue=0.0;
    if(red   > 1.0) red=1.0;
    if(green > 1.0) green=1.0;
    if(blue  > 1.0) blue=1.0;

    switch(devp->t) {
      case g2_PD:
	rv=g2_ink_pd(devp->d.pd, red, green, blue);
	break;
      case g2_VD:
	fprintf(stderr, "g2_ink: g2_ink is enabled only for phys. devices\n");
	break;
      case g2_ILLEGAL:
	break;
      case g2_NDEV:
	break;
    }
    __g2_last_device=pd_dev;
    return rv;
}
