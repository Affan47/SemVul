hdlc_xdu_irq(struct fritz_bcs *bcs)
{
	struct fritz_adapter *adapter = bcs->adapter;


	bcs->ctrl.sr.xml = 0;
	bcs->ctrl.sr.cmd |= HDLC_CMD_XRS;
	adapter->write_ctrl(bcs, 1);
	bcs->ctrl.sr.cmd &= ~HDLC_CMD_XRS;

	if (!bcs->tx_skb) {
		DBG(0x10, "XDU without skb");
		adapter->write_ctrl(bcs, 1);
		return;
	}

	if (bcs->mode == L1_MODE_HDLC) {
		skb_push(bcs->tx_skb, bcs->tx_cnt);
		bcs->tx_cnt = 0;
	}
}
