b1_register_appl(struct capi_ctr *ctrl,
		      u16 appl,
		      capi_register_params *rp)
{
	avmctrl_info *cinfo = (avmctrl_info *)(ctrl->driverdata);
	avmcard *card = cinfo->card;
	unsigned int port = card->port;
	unsigned long flags;
	int nconn, want = rp->level3cnt;

	if (want > 0) nconn = want;
	else nconn = ctrl->profile.nbchannel * -want;
	if (nconn == 0) nconn = ctrl->profile.nbchannel;

	spin_lock_irqsave(&card->lock, flags);
	b1_put_byte(port, SEND_REGISTER);
	b1_put_word(port, appl);
	b1_put_word(port, 1024 * (nconn + 1));
	b1_put_word(port, nconn);
	b1_put_word(port, rp->datablkcnt);
	b1_put_word(port, rp->datablklen);
	spin_unlock_irqrestore(&card->lock, flags);
}
