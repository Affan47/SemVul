cmd_prereq(const char* lp, nsupdate_params_t *params)
{
	DBG("%s: lp='%s'\n", __func__, lp);


	int ret = KNOT_EOK;
	int bp = tok_find(lp, pq_array);
	if (bp < 0) return bp;

	const char *tok = pq_array[bp];
	DBG("%s: type %s\n", __func__, TOK_S(tok));
	lp = tok_skipspace(lp + TOK_L(tok));
	switch(bp) {
	case PQ_NXDOMAIN:
	case PQ_YXDOMAIN:
		ret = cmd_prereq_domain(lp, params, bp);
		break;
	case PQ_NXRRSET:
	case PQ_YXRRSET:
		ret = cmd_prereq_rrset(lp, params, bp);
		break;
	default:
		return KNOT_ERROR;
	}


	if (ret == KNOT_EOK) {
		scanner_t *s = params->rrp;
		s->r_ttl = 0;

		if (bp == PQ_YXRRSET || bp == PQ_YXDOMAIN) {
			s->r_class = KNOT_CLASS_ANY;
		} else {
			s->r_class = KNOT_CLASS_NONE;
		}

		ret = pkt_append(params, bp);
	}

	return ret;
}
