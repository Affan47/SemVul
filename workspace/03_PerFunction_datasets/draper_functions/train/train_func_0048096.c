fotg210_iaa_watchdog(struct fotg210_hcd *fotg210)
{
	if (fotg210->rh_state != FOTG210_RH_RUNNING)
		return;


	if (fotg210->async_iaa) {
		u32 cmd, status;


		cmd = fotg210_readl(fotg210, &fotg210->regs->command);


		status = fotg210_readl(fotg210, &fotg210->regs->status);
		if ((status & STS_IAA) || !(cmd & CMD_IAAD)) {
			COUNT(fotg210->stats.lost_iaa);
			fotg210_writel(fotg210, STS_IAA,
					&fotg210->regs->status);
		}

		fotg210_dbg(fotg210, "IAA watchdog: status %x cmd %x\n",
				status, cmd);
		end_unlink_async(fotg210);
	}
}
