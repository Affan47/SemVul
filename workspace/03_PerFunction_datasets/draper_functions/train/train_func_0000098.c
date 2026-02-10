bfa_cb_sfp_show(struct bfa_sfp_s *sfp)
{
	bfa_trc(sfp, sfp->lock);
	if (sfp->cbfn)
		sfp->cbfn(sfp->cbarg, sfp->status);
	sfp->lock = 0;
	sfp->cbfn = NULL;
}
