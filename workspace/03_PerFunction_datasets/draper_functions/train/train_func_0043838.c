setup_instance(struct tiger_hw *card)
{
	int i, err;
	u_long flags;

	snprintf(card->name, MISDN_MAX_IDLEN - 1, "netjet.%d", nj_cnt + 1);
	write_lock_irqsave(&card_lock, flags);
	list_add_tail(&card->list, &Cards);
	write_unlock_irqrestore(&card_lock, flags);

	_set_debug(card);
	card->isac.name = card->name;
	spin_lock_init(&card->lock);
	card->isac.hwlock = &card->lock;
	mISDNisac_init(&card->isac, card);

	card->isac.dch.dev.Bprotocols = (1 << (ISDN_P_B_RAW & ISDN_P_B_MASK)) |
		(1 << (ISDN_P_B_HDLC & ISDN_P_B_MASK));
	card->isac.dch.dev.D.ctrl = nj_dctrl;
	for (i = 0; i < 2; i++) {
		card->bc[i].bch.nr = i + 1;
		set_channelmap(i + 1, card->isac.dch.dev.channelmap);
		mISDN_initbchannel(&card->bc[i].bch, MAX_DATA_MEM,
				   NJ_DMA_RXSIZE >> 1);
		card->bc[i].bch.hw = card;
		card->bc[i].bch.ch.send = nj_l2l1B;
		card->bc[i].bch.ch.ctrl = nj_bctrl;
		card->bc[i].bch.ch.nr = i + 1;
		list_add(&card->bc[i].bch.ch.list,
			 &card->isac.dch.dev.bchannels);
		card->bc[i].bch.hw = card;
	}
	err = nj_setup(card);
	if (err)
		goto error;
	err = mISDN_register_device(&card->isac.dch.dev, &card->pdev->dev,
				    card->name);
	if (err)
		goto error;
	err = nj_init_card(card);
	if (!err)  {
		nj_cnt++;
		pr_notice("Netjet %d cards installed\n", nj_cnt);
		return 0;
	}
error:
	nj_release(card);
	return err;
}
