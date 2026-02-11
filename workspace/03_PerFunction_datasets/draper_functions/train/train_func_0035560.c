mbox_controller_register(struct mbox_controller *mbox)
{
	int i, txdone;


	if (!mbox || !mbox->dev || !mbox->ops || !mbox->num_chans)
		return -EINVAL;

	if (mbox->txdone_irq)
		txdone = TXDONE_BY_IRQ;
	else if (mbox->txdone_poll)
		txdone = TXDONE_BY_POLL;
	else
		txdone = TXDONE_BY_ACK;

	if (txdone == TXDONE_BY_POLL) {
		hrtimer_init(&mbox->poll_hrt, CLOCK_MONOTONIC,
			     HRTIMER_MODE_REL);
		mbox->poll_hrt.function = txdone_hrtimer;
	}

	for (i = 0; i < mbox->num_chans; i++) {
		struct mbox_chan *chan = &mbox->chans[i];

		chan->cl = NULL;
		chan->mbox = mbox;
		chan->txdone_method = txdone;
		spin_lock_init(&chan->lock);
	}

	if (!mbox->of_xlate)
		mbox->of_xlate = of_mbox_index_xlate;

	mutex_lock(&con_mutex);
	list_add_tail(&mbox->node, &mbox_cons);
	mutex_unlock(&con_mutex);

	return 0;
}
