isdn_tty_tint(modem_info *info)
{
	struct sk_buff *skb = skb_dequeue(&info->xmit_queue);
	int len, slen;

	if (!skb)
		return;
	len = skb->len;
	if ((slen = isdn_writebuf_skb_stub(info->isdn_driver,
					   info->isdn_channel, 1, skb)) == len) {
		struct tty_struct *tty = info->port.tty;
		info->send_outstanding++;
		info->msr &= ~UART_MSR_CTS;
		info->lsr &= ~UART_LSR_TEMT;
		tty_wakeup(tty);
		return;
	}
	if (slen < 0) {

		dev_kfree_skb(skb);
		return;
	}
	skb_queue_head(&info->xmit_queue, skb);
}
