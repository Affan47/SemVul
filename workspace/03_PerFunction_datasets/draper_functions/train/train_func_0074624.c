trf7970a_drain_fifo(struct trf7970a *trf, u8 status)
{
	struct sk_buff *skb = trf->rx_skb;
	int ret;
	u8 fifo_bytes;

	if (status & TRF7970A_IRQ_STATUS_ERROR) {
		trf7970a_send_err_upstream(trf, -EIO);
		return;
	}

	ret = trf7970a_read(trf, TRF7970A_FIFO_STATUS, &fifo_bytes);
	if (ret) {
		trf7970a_send_err_upstream(trf, ret);
		return;
	}

	dev_dbg(trf->dev, "Draining FIFO - fifo_bytes: 0x%x\n", fifo_bytes);

	fifo_bytes &= ~TRF7970A_FIFO_STATUS_OVERFLOW;

	if (!fifo_bytes)
		goto no_rx_data;

	if (fifo_bytes > skb_tailroom(skb)) {
		skb = skb_copy_expand(skb, skb_headroom(skb),
				max_t(int, fifo_bytes,
					TRF7970A_RX_SKB_ALLOC_SIZE),
				GFP_KERNEL);
		if (!skb) {
			trf7970a_send_err_upstream(trf, -ENOMEM);
			return;
		}

		kfree_skb(trf->rx_skb);
		trf->rx_skb = skb;
	}

	ret = trf7970a_read_cont(trf, TRF7970A_FIFO_IO_REGISTER,
			skb_put(skb, fifo_bytes), fifo_bytes);
	if (ret) {
		trf7970a_send_err_upstream(trf, ret);
		return;
	}


	if ((trf->framing == NFC_DIGITAL_FRAMING_NFCA_T2T) && (skb->len == 1) &&
			(trf->special_fcn_reg1 ==
				 TRF7970A_SPECIAL_FCN_REG1_4_BIT_RX)) {
		skb->data[0] >>= 4;
		status = TRF7970A_IRQ_STATUS_SRX;
	} else {
		trf->state = TRF7970A_ST_WAIT_FOR_RX_DATA_CONT;

		ret = trf7970a_read(trf, TRF7970A_FIFO_STATUS, &fifo_bytes);
		if (ret) {
			trf7970a_send_err_upstream(trf, ret);
			return;
		}

		fifo_bytes &= ~TRF7970A_FIFO_STATUS_OVERFLOW;


		if (fifo_bytes)
			status = 0;
	}

no_rx_data:
	if (status == TRF7970A_IRQ_STATUS_SRX) {
		trf7970a_send_upstream(trf);
		return;
	}

	dev_dbg(trf->dev, "Setting timeout for %d ms\n",
			TRF7970A_WAIT_FOR_RX_DATA_TIMEOUT);

	schedule_delayed_work(&trf->timeout_work,
			msecs_to_jiffies(TRF7970A_WAIT_FOR_RX_DATA_TIMEOUT));
}
