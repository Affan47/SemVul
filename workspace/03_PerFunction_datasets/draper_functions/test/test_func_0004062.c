ata_rw_frameinit(struct frame *f)
{
	struct aoetgt *t;
	struct aoe_hdr *h;
	struct aoe_atahdr *ah;
	struct sk_buff *skb;
	char writebit, extbit;

	skb = f->skb;
	h = (struct aoe_hdr *) skb_mac_header(skb);
	ah = (struct aoe_atahdr *) (h + 1);
	skb_put(skb, sizeof(*h) + sizeof(*ah));
	memset(h, 0, skb->len);

	writebit = 0x10;
	extbit = 0x4;

	t = f->t;
	f->tag = aoehdr_atainit(t->d, t, h);
	fhash(f);
	t->nout++;
	f->waited = 0;
	f->waited_total = 0;


	ah->scnt = f->iter.bi_size >> 9;
	put_lba(ah, f->iter.bi_sector);
	if (t->d->flags & DEVFL_EXT) {
		ah->aflags |= AOEAFL_EXT;
	} else {
		extbit = 0;
		ah->lba3 &= 0x0f;
		ah->lba3 |= 0xe0;
	}
	if (f->buf && bio_data_dir(f->buf->bio) == WRITE) {
		skb_fillup(skb, f->buf->bio, f->iter);
		ah->aflags |= AOEAFL_WRITE;
		skb->len += f->iter.bi_size;
		skb->data_len = f->iter.bi_size;
		skb->truesize += f->iter.bi_size;
		t->wpkts++;
	} else {
		t->rpkts++;
		writebit = 0;
	}

	ah->cmdstat = ATA_CMD_PIO_READ | writebit | extbit;
	skb->dev = t->ifp->nd;
}
