de4x5_bad_srom(struct de4x5_private *lp)
{
    int i, status = 0;

    for (i = 0; i < ARRAY_SIZE(enet_det); i++) {
	if (!memcmp(&lp->srom, &enet_det[i], 3) &&
	    !memcmp((char *)&lp->srom+0x10, &enet_det[i], 3)) {
	    if (i == 0) {
		status = SMC;
	    } else if (i == 1) {
		status = ACCTON;
	    }
	    break;
	}
    }

    return status;
}
