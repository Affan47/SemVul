link_down(unit)
    int unit;
{
    int i;
    struct protent *protp;

    for (i = 0; (protp = protocols[i]) != NULL; ++i) {
        if (protp->protocol != PPP_LCP && protp->lowerdown != NULL)
	    (*protp->lowerdown)(unit);
        if (protp->protocol < 0xC000 && protp->close != NULL)
	    (*protp->close)(unit);
    }
    phase = PHASE_TERMINATE;
}
