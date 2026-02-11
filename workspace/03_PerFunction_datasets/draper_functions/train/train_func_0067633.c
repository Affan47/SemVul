isdn_tty_at_cout(char *msg, modem_info *info)
{
	struct tty_port *port = &info->port;
	atemu *m = &info->emu;
	char *p;
	char c;
	u_long flags;
	struct sk_buff *skb = NULL;
	char *sp = NULL;
	int l;

	if (!msg) {
		printk(KERN_WARNING "isdn_tty: Null-Message in isdn_tty_at_cout\n");
		return;
	}

	l = strlen(msg);

	spin_lock_irqsave(&info->readlock, flags);
	if (port->flags & ASYNC_CLOSING) {
		spin_unlock_irqrestore(&info->readlock, flags);
		return;
	}


	if (info->online && ((tty_buffer_request_room(port, l) < l) ||
			     !skb_queue_empty(&dev->drv[info->isdn_driver]->rpqueue[info->isdn_channel]))) {
		skb = alloc_skb(l, GFP_ATOMIC);
		if (!skb) {
			spin_unlock_irqrestore(&info->readlock, flags);
			return;
		}
		sp = skb_put(skb, l);
#ifdef CONFIG_ISDN_AUDIO
		ISDN_AUDIO_SKB_DLECOUNT(skb) = 0;
		ISDN_AUDIO_SKB_LOCK(skb) = 0;
#endif
	}

	for (p = msg; *p; p++) {
		switch (*p) {
		case '\r':
			c = m->mdmreg[REG_CR];
			break;
		case '\n':
			c = m->mdmreg[REG_LF];
			break;
		case '\b':
			c = m->mdmreg[REG_BS];
			break;
		default:
			c = *p;
		}
		if (skb) {
			*sp++ = c;
		} else {
			if (tty_insert_flip_char(port, c, TTY_NORMAL) == 0)
				break;
		}
	}
	if (skb) {
		__skb_queue_tail(&dev->drv[info->isdn_driver]->rpqueue[info->isdn_channel], skb);
		dev->drv[info->isdn_driver]->rcvcount[info->isdn_channel] += skb->len;
		spin_unlock_irqrestore(&info->readlock, flags);

		if (dev->modempoll && info->rcvsched)
			isdn_timer_ctrl(ISDN_TIMER_MODEMREAD, 1);

	} else {
		spin_unlock_irqrestore(&info->readlock, flags);
		tty_flip_buffer_push(port);
	}
}
