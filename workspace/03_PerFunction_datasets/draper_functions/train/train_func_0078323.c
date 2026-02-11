open_bchannel(struct hfcsusb *hw, struct channel_req *rq)
{
	struct bchannel		*bch;

	if (rq->adr.channel == 0 || rq->adr.channel > 2)
		return -EINVAL;
	if (rq->protocol == ISDN_P_NONE)
		return -EINVAL;

	if (debug & DBG_HFC_CALL_TRACE)
		printk(KERN_DEBUG "%s: %s B%i\n",
		       hw->name, __func__, rq->adr.channel);

	bch = &hw->bch[rq->adr.channel - 1];
	if (test_and_set_bit(FLG_OPEN, &bch->Flags))
		return -EBUSY;
	bch->ch.protocol = rq->protocol;
	rq->ch = &bch->ch;

	if (!try_module_get(THIS_MODULE))
		printk(KERN_WARNING "%s: %s:cannot get module\n",
		       hw->name, __func__);
	return 0;
}
