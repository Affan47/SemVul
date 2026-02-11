read_lcb_csr(struct hfi1_devdata *dd, u32 addr, u64 *data)
{
	struct hfi1_pportdata *ppd = dd->pport;


	if (ppd->host_link_state & HLS_UP)
		return read_lcb_via_8051(dd, addr, data);

	if (ppd->host_link_state & (HLS_GOING_UP | HLS_GOING_OFFLINE))
		return -EBUSY;

	*data = read_csr(dd, addr);
	return 0;
}
