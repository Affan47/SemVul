dgap_set_modem_info(struct channel_t *ch, struct board_t *bd,
			       struct un_t *un, unsigned int command,
			       unsigned int __user *value)
{
	int ret;
	unsigned int arg;
	ulong lock_flags;
	ulong lock_flags2;

	ret = get_user(arg, value);
	if (ret)
		return ret;

	switch (command) {
	case TIOCMBIS:
		if (arg & TIOCM_RTS) {
			ch->ch_mforce |= D_RTS(ch);
			ch->ch_mval   |= D_RTS(ch);
		}

		if (arg & TIOCM_DTR) {
			ch->ch_mforce |= D_DTR(ch);
			ch->ch_mval   |= D_DTR(ch);
		}

		break;

	case TIOCMBIC:
		if (arg & TIOCM_RTS) {
			ch->ch_mforce |= D_RTS(ch);
			ch->ch_mval   &= ~(D_RTS(ch));
		}

		if (arg & TIOCM_DTR) {
			ch->ch_mforce |= D_DTR(ch);
			ch->ch_mval   &= ~(D_DTR(ch));
		}

		break;

	case TIOCMSET:
		ch->ch_mforce = D_DTR(ch) | D_RTS(ch);

		if (arg & TIOCM_RTS)
			ch->ch_mval |= D_RTS(ch);
		else
			ch->ch_mval &= ~(D_RTS(ch));

		if (arg & TIOCM_DTR)
			ch->ch_mval |= (D_DTR(ch));
		else
			ch->ch_mval &= ~(D_DTR(ch));

		break;

	default:
		return -EINVAL;
	}

	spin_lock_irqsave(&bd->bd_lock, lock_flags);
	spin_lock_irqsave(&ch->ch_lock, lock_flags2);

	dgap_param(ch, bd, un->un_type);

	spin_unlock_irqrestore(&ch->ch_lock, lock_flags2);
	spin_unlock_irqrestore(&bd->bd_lock, lock_flags);

	return 0;
}
