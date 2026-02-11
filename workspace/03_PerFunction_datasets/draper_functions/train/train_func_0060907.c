upd_npdel(const int row, struct sctrl *scp)
{
	int	num = wnum(jscr, row, scp, (LONG) JREQ.spq_nptimeout);
	if  (num > 0  &&  num != (int) JREQ.spq_nptimeout)  {
		JREQ.spq_nptimeout = (USHORT) num;
		return  -1;
	}
	return  0;
}
