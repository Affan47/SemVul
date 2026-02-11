mppe_init(struct ppp_ccp_t *ccp)
{
	struct mppe_option_t *mppe_opt = _malloc(sizeof(*mppe_opt));
	memset(mppe_opt, 0, sizeof(*mppe_opt));
	int mppe;

	if (ccp->ppp->ses.ctrl->mppe == MPPE_UNSET)
		mppe = conf_mppe;
	else
		mppe = ccp->ppp->ses.ctrl->mppe;

	if (mppe != MPPE_ALLOW)
		mppe_opt->policy = mppe;
	else
		mppe_opt->policy = 1;

	if (mppe > 0)
		mppe_opt->mppe = 1;
	else
		mppe_opt->mppe = -1;

	if (mppe == MPPE_REQUIRE || mppe == MPPE_PREFER)
		ccp->ld.passive = 0;

	if (mppe == MPPE_REQUIRE)
		ccp->ld.optional = 0;

	if (mppe == MPPE_REQUIRE)
		ccp->ld.optional = 0;

	mppe_opt->opt.id = CI_MPPE;
	mppe_opt->opt.len = 6;

	return &mppe_opt->opt;
}
