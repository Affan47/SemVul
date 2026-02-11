lcp_lowerdown(unit)
    int unit;
{
    fsm *f = &lcp_fsm[unit];

    if (f->flags & DELAYED_UP)
	f->flags &= ~DELAYED_UP;
    else
	fsm_lowerdown(&lcp_fsm[unit]);
}
