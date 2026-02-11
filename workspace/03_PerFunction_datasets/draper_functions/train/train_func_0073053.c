hfi1_bad_pqkey(struct hfi1_ibport *ibp, __be16 trap_num, u32 key, u32 sl,
		    u32 qp1, u32 qp2, __be16 lid1, __be16 lid2)
{
	struct ib_mad_notice_attr data;

	if (trap_num == IB_NOTICE_TRAP_BAD_PKEY)
		ibp->pkey_violations++;
	else
		ibp->qkey_violations++;
	ibp->n_pkt_drops++;


	data.generic_type = IB_NOTICE_TYPE_SECURITY;
	data.prod_type_msb = 0;
	data.prod_type_lsb = IB_NOTICE_PROD_CA;
	data.trap_num = trap_num;
	data.issuer_lid = cpu_to_be16(ppd_from_ibp(ibp)->lid);
	data.toggle_count = 0;
	memset(&data.details, 0, sizeof(data.details));
	data.details.ntc_257_258.lid1 = lid1;
	data.details.ntc_257_258.lid2 = lid2;
	data.details.ntc_257_258.key = cpu_to_be32(key);
	data.details.ntc_257_258.sl_qp1 = cpu_to_be32((sl << 28) | qp1);
	data.details.ntc_257_258.qp2 = cpu_to_be32(qp2);

	send_trap(ibp, &data, sizeof(data));
}
