dgnc_tty_send_xchar(struct tty_struct *tty, char c)
{
	struct dgnc_board *bd;
	struct channel_t *ch;
	struct un_t *un;
	unsigned long flags;

	if (!tty || tty->magic != TTY_MAGIC)
		return;

	un = tty->driver_data;
	if (!un || un->magic != DGNC_UNIT_MAGIC)
		return;

	ch = un->un_ch;
	if (!ch || ch->magic != DGNC_CHANNEL_MAGIC)
		return;

	bd = ch->ch_bd;
	if (!bd || bd->magic != DGNC_BOARD_MAGIC)
		return;

	dev_dbg(tty->dev, "dgnc_tty_send_xchar start\n");

	spin_lock_irqsave(&ch->ch_lock, flags);
	bd->bd_ops->send_immediate_char(ch, c);
	spin_unlock_irqrestore(&ch->ch_lock, flags);

	dev_dbg(tty->dev, "dgnc_tty_send_xchar finish\n");
}
