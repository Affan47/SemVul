__subn_get_opa_cong_info(struct opa_smp *smp, u32 am, u8 *data,
				    struct ib_device *ibdev, u8 port,
				    u32 *resp_len)
{
	struct opa_congestion_info_attr *p =
		(struct opa_congestion_info_attr *)data;
	struct hfi1_ibport *ibp = to_iport(ibdev, port);
	struct hfi1_pportdata *ppd = ppd_from_ibp(ibp);

	p->congestion_info = 0;
	p->control_table_cap = ppd->cc_max_table_entries;
	p->congestion_log_length = OPA_CONG_LOG_ELEMS;

	if (resp_len)
		*resp_len += sizeof(*p);

	return reply((struct ib_mad_hdr *)smp);
}
