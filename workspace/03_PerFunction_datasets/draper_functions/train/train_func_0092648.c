fotg210_quiesce(struct fotg210_hcd *fotg210)
{
	u32 temp;

	if (fotg210->rh_state != FOTG210_RH_RUNNING)
		return;


	temp = (fotg210->command << 10) & (STS_ASS | STS_PSS);
	handshake(fotg210, &fotg210->regs->status, STS_ASS | STS_PSS, temp,
			16 * 125);


	spin_lock_irq(&fotg210->lock);
	fotg210->command &= ~(CMD_ASE | CMD_PSE);
	fotg210_writel(fotg210, fotg210->command, &fotg210->regs->command);
	spin_unlock_irq(&fotg210->lock);


	handshake(fotg210, &fotg210->regs->status, STS_ASS | STS_PSS, 0,
			16 * 125);
}
