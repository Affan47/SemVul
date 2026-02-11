brcms_c_txfifo(struct brcms_c_info *wlc, uint fifo, struct sk_buff *p)
{
	struct dma_pub *dma = wlc->hw->di[fifo];
	int ret;
	u16 queue;

	ret = dma_txfast(wlc, dma, p);
	if (ret	< 0)
		wiphy_err(wlc->wiphy, "txfifo: fatal, toss frames !!!\n");


	queue = skb_get_queue_mapping(p);
	if (dma->txavail <= TX_HEADROOM && fifo < TX_BCMC_FIFO &&
	    !ieee80211_queue_stopped(wlc->pub->ieee_hw, queue))
		ieee80211_stop_queue(wlc->pub->ieee_hw, queue);

	return ret;
}
