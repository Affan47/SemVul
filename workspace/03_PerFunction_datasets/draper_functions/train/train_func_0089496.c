ars_add_ipopt(struct ars_packet *pkt, int option)
{
	int retval;
	struct ars_ipopt *ipopt;
	int opt_len;

	switch(option) {
	case ARS_IPOPT_END:
	case ARS_IPOPT_NOOP:
		opt_len = 1;
		break;
	case ARS_IPOPT_SEC:
		opt_len = 11;
		break;
	case ARS_IPOPT_SID:
		opt_len = 4;
		break;
	case ARS_IPOPT_LSRR:
	case ARS_IPOPT_SSRR:
	case ARS_IPOPT_RR:
	case ARS_IPOPT_TIMESTAMP:


		opt_len = 40;
		break;
	default:
		return NULL;
		break;
	}

	retval = ars_add_generic(pkt, opt_len, ARS_TYPE_IPOPT);
	if (retval != -ARS_OK)
		return NULL;
	ipopt = pkt->p_layer[pkt->p_layer_nr].l_data;
	pkt->p_layer_nr++;

	ipopt->kind = option;

	if (option == ARS_IPOPT_END || option == ARS_IPOPT_NOOP)
		return ipopt;
	ipopt->len = opt_len;

	switch(option) {
	case ARS_IPOPT_LSRR:
	case ARS_IPOPT_SSRR:
	case ARS_IPOPT_RR:


		ipopt->len = opt_len - 2 - 3;
		ipopt->un.rr.ptr = 4;
		break;
	case ARS_IPOPT_TIMESTAMP:
		ipopt->len = opt_len - 2 - 4;
		ipopt->un.ts.ptr = 5;
		ipopt->un.ts.flags = ARS_IPOPT_TS_TSONLY;
		break;
	}
	return ipopt;
}
