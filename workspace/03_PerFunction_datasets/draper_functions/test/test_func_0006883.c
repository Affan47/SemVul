disable_chase(struct qib_pportdata *ppd, unsigned long tnow,
		u8 ibclt)
{
	ppd->cpspec->chase_end = 0;

	if (!qib_chase)
		return;

	qib_set_ib_7322_lstate(ppd, QLOGIC_IB_IBCC_LINKCMD_DOWN,
		QLOGIC_IB_IBCC_LINKINITCMD_DISABLE);
	ppd->cpspec->chase_timer.expires = jiffies + QIB_CHASE_DIS_TIME;
	add_timer(&ppd->cpspec->chase_timer);
}
