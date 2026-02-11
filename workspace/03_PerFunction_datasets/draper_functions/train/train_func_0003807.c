st_wakeup_ack(struct st_data_s *st_gdata,
	unsigned char cmd)
{
	struct sk_buff *waiting_skb;
	unsigned long flags = 0;

	spin_lock_irqsave(&st_gdata->lock, flags);


	while ((waiting_skb = skb_dequeue(&st_gdata->tx_waitq)))
		skb_queue_tail(&st_gdata->txq, waiting_skb);


	st_ll_sleep_state(st_gdata, (unsigned long)cmd);
	spin_unlock_irqrestore(&st_gdata->lock, flags);


	st_tx_wakeup(st_gdata);
}
