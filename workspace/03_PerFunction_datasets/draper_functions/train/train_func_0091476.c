type5_infoblock(struct net_device *dev, u_char count, u_char *p)
{
    struct de4x5_private *lp = netdev_priv(dev);
    u_char len = (*p & BLOCK_LEN)+1;


    if (--count > lp->tcount) {
	if (*(p+len) < 128) {
	    return dc_infoblock[COMPACT](dev, count, p+len);
	} else {
	    return dc_infoblock[*(p+len+1)](dev, count, p+len);
	}
    }


    if ((lp->state == INITIALISED) || (lp->media == INIT)) {
	p+=2;
        lp->rst = p;
        srom_exec(dev, lp->rst);
    }

    return DE4X5_AUTOSENSE_MS;
}
