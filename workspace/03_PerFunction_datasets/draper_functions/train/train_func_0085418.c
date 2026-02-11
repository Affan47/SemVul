isar_open(struct isar_hw *isar, struct channel_req *rq)
{
	struct bchannel		*bch;

	if (rq->adr.channel == 0 || rq->adr.channel > 2)
		return -EINVAL;
	if (rq->protocol == ISDN_P_NONE)
		return -EINVAL;
	bch = &isar->ch[rq->adr.channel - 1].bch;
	if (test_and_set_bit(FLG_OPEN, &bch->Flags))
		return -EBUSY;
	bch->ch.protocol = rq->protocol;
	rq->ch = &bch->ch;
	return 0;
}
