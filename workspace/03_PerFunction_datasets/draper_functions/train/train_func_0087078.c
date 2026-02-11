__subn_get_opa_sc_to_vlnt(struct opa_smp *smp, u32 am, u8 *data,
				     struct ib_device *ibdev, u8 port,
				     u32 *resp_len)
{
	u32 n_blocks = OPA_AM_NPORT(am);
	struct hfi1_devdata *dd = dd_from_ibdev(ibdev);
	struct hfi1_pportdata *ppd;
	void *vp = (void *) data;
	int size;

	if (n_blocks != 1) {
		smp->status |= IB_SMP_INVALID_FIELD;
		return reply((struct ib_mad_hdr *)smp);
	}

	ppd = dd->pport + (port - 1);

	size = fm_get_table(ppd, FM_TBL_SC2VLNT, vp);

	if (resp_len)
		*resp_len += size;

	return reply((struct ib_mad_hdr *)smp);
}
