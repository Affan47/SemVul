ev_mppe_keys(struct ev_mppe_keys_t *ev)
{
	struct ppp_ccp_t *ccp = ccp_find_layer_data(ev->ppp);
	struct mppe_option_t *mppe_opt = container_of(ccp_find_option(ev->ppp, &mppe_opt_hnd), typeof(*mppe_opt), opt);
	int mppe;

	memcpy(mppe_opt->recv_key, ev->recv_key, 16);
	memcpy(mppe_opt->send_key, ev->send_key, 16);

	if (ev->policy == -1)
		return;

	if ((ev->type & 0x04) == 0) {
		log_ppp_warn("mppe: 128-bit session keys not allowed, disabling mppe ...\n");
		mppe_opt->mppe = 0;
		return;
	}

	if (ccp->ppp->ses.ctrl->mppe == MPPE_UNSET)
		mppe = conf_mppe;
	else
		mppe = ev->ppp->ses.ctrl->mppe;

	if (ev->ppp->ses.ctrl->mppe == MPPE_UNSET) {
		mppe_opt->policy = ev->policy;

		if (ev->policy == 2) {
			mppe_opt->mppe = 1;
			ccp->ld.passive = 0;
		} else if (ev->policy == 1) {
			if (mppe == 1)
				mppe_opt->mppe = 1;
			else
				mppe_opt->mppe = -1;

			if (mppe == 2)
				ccp->ld.passive = 1;
		}
	}
}
