vt_ctrl_CUD(struct cpssp *cpssp, unsigned int amount)
{
	int i;

	if (amount == 0) {
		amount = 1;
	}
	i = cpssp->ts.row + amount;
	TRACE("CUD: relative %u absolute %d\n", amount, i);
	if ((int) cpssp->ts.bottom < i) {
		i = cpssp->ts.bottom;
		TRACE("CUD: using bottom margin %d\n", i);
	}
	cpssp->ts.row = i;
}
