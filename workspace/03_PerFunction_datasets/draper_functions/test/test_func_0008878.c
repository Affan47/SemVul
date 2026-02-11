trf7970a_fill_fifo(struct trf7970a *trf)
{
	struct sk_buff *skb = trf->tx_skb;
	unsigned int len;
	int ret;
	u8 fifo_bytes;
	u8 prefix;

	ret = trf7970a_read(trf, TRF7970A_FIFO_STATUS, &fifo_bytes);
	if (ret) {
		trf7970a_send_err_upstream(trf, ret);
		return;
	}

	dev_dbg(trf->dev, "Filling FIFO - fifo_bytes: 0x%x\n", fifo_bytes);

	fifo_bytes &= ~TRF7970A_FIFO_STATUS_OVERFLOW;


	len = TRF7970A_FIFO_SIZE - fifo_bytes;
	if (!len) {
		schedule_delayed_work(&trf->timeout_work,
			msecs_to_jiffies(TRF7970A_WAIT_FOR_FIFO_DRAIN_TIMEOUT));
		return;
	}

	len = min(skb->len, len);

	prefix = TRF7970A_CMD_BIT_CONTINUOUS | TRF7970A_FIFO_IO_REGISTER;

	ret = trf7970a_transmit(trf, skb, len, &prefix, sizeof(prefix));
	if (ret)
		trf7970a_send_err_upstream(trf, ret);
}
