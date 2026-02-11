cy_tiocmset(struct tty_struct *tty,
		unsigned int set, unsigned int clear)
{
	struct cyclades_port *info = tty->driver_data;
	struct cyclades_card *card;
	unsigned long flags;

	if (serial_paranoia_check(info, tty->name, __func__))
		return -ENODEV;

	card = info->card;
	if (!cy_is_Z(card)) {
		spin_lock_irqsave(&card->card_lock, flags);
		cyy_change_rts_dtr(info, set, clear);
		spin_unlock_irqrestore(&card->card_lock, flags);
	} else {
		struct CH_CTRL __iomem *ch_ctrl = info->u.cyz.ch_ctrl;
		int retval, channel = info->line - card->first_line;
		u32 rs;

		if (!cyz_is_loaded(card))
			return -ENODEV;

		spin_lock_irqsave(&card->card_lock, flags);
		rs = readl(&ch_ctrl->rs_control);
		if (set & TIOCM_RTS)
			rs |= C_RS_RTS;
		if (clear & TIOCM_RTS)
			rs &= ~C_RS_RTS;
		if (set & TIOCM_DTR) {
			rs |= C_RS_DTR;
#ifdef CY_DEBUG_DTR
			printk(KERN_DEBUG "cyc:set_modem_info raising Z DTR\n");
#endif
		}
		if (clear & TIOCM_DTR) {
			rs &= ~C_RS_DTR;
#ifdef CY_DEBUG_DTR
			printk(KERN_DEBUG "cyc:set_modem_info clearing "
				"Z DTR\n");
#endif
		}
		cy_writel(&ch_ctrl->rs_control, rs);
		retval = cyz_issue_cmd(card, channel, C_CM_IOCTLM, 0L);
		spin_unlock_irqrestore(&card->card_lock, flags);
		if (retval != 0) {
			printk(KERN_ERR "cyc:set_modem_info retval on ttyC%d "
				"was %x\n", info->line, retval);
		}
	}
	return 0;
}
