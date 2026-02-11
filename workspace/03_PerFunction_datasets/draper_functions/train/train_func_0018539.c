set_vls(struct qib_pportdata *ppd)
{
	int i, numvls, totcred, cred_vl, vl0extra;
	struct qib_devdata *dd = ppd->dd;
	u64 val;

	numvls = qib_num_vls(ppd->vls_operational);


	totcred = NUM_RCV_BUF_UNITS(dd);
	cred_vl = (2 * 288 + RCV_BUF_UNITSZ - 1) / RCV_BUF_UNITSZ;
	totcred -= cred_vl;
	qib_write_kreg_port(ppd, krp_rxcreditvl15, (u64) cred_vl);
	cred_vl = totcred / numvls;
	vl0extra = totcred - cred_vl * numvls;
	qib_write_kreg_port(ppd, krp_rxcreditvl0, cred_vl + vl0extra);
	for (i = 1; i < numvls; i++)
		qib_write_kreg_port(ppd, krp_rxcreditvl0 + i, cred_vl);
	for (; i < 8; i++)
		qib_write_kreg_port(ppd, krp_rxcreditvl0 + i, 0);


	val = qib_read_kreg_port(ppd, krp_ibsdtestiftx);
	val |= SYM_MASK(IB_SDTEST_IF_TX_0, CREDIT_CHANGE);
	qib_write_kreg_port(ppd, krp_ibsdtestiftx, val);
	qib_write_kreg(dd, kr_scratch, 0ULL);
	val &= ~SYM_MASK(IB_SDTEST_IF_TX_0, CREDIT_CHANGE);
	qib_write_kreg_port(ppd, krp_ibsdtestiftx, val);

	for (i = 0; i < numvls; i++)
		val = qib_read_kreg_port(ppd, krp_rxcreditvl0 + i);
	val = qib_read_kreg_port(ppd, krp_rxcreditvl15);


	ppd->cpspec->ibcctrl_a = (ppd->cpspec->ibcctrl_a &
				~SYM_MASK(IBCCtrlA_0, NumVLane)) |
		((u64)(numvls - 1) << SYM_LSB(IBCCtrlA_0, NumVLane));
	qib_write_kreg_port(ppd, krp_ibcctrl_a, ppd->cpspec->ibcctrl_a);
	qib_write_kreg(dd, kr_scratch, 0ULL);
}
