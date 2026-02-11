close_hdlcstate(struct BCState *bcs)
{
	modehdlc(bcs, 0, 0);
	if (test_and_clear_bit(BC_FLG_INIT, &bcs->Flag)) {
		kfree(bcs->hw.hdlc.rcvbuf);
		bcs->hw.hdlc.rcvbuf = NULL;
		kfree(bcs->blog);
		bcs->blog = NULL;
		skb_queue_purge(&bcs->rqueue);
		skb_queue_purge(&bcs->squeue);
		if (bcs->tx_skb) {
			dev_kfree_skb_any(bcs->tx_skb);
			bcs->tx_skb = NULL;
			test_and_clear_bit(BC_FLG_BUSY, &bcs->Flag);
		}
	}
}
