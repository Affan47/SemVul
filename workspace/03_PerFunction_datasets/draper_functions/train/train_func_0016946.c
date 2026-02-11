collect_adapter_stats(struct adapter *adap, struct adapter_stats *s)
{
	struct tp_tcp_stats v4, v6;
	struct tp_rdma_stats rdma_stats;
	struct tp_err_stats err_stats;
	struct tp_usm_stats usm_stats;
	u64 val1, val2;

	memset(s, 0, sizeof(*s));

	spin_lock(&adap->stats_lock);
	t4_tp_get_tcp_stats(adap, &v4, &v6);
	t4_tp_get_rdma_stats(adap, &rdma_stats);
	t4_get_usm_stats(adap, &usm_stats);
	t4_tp_get_err_stats(adap, &err_stats);
	spin_unlock(&adap->stats_lock);

	s->db_drop = adap->db_stats.db_drop;
	s->db_full = adap->db_stats.db_full;
	s->db_empty = adap->db_stats.db_empty;

	s->tcp_v4_out_rsts = v4.tcp_out_rsts;
	s->tcp_v4_in_segs = v4.tcp_in_segs;
	s->tcp_v4_out_segs = v4.tcp_out_segs;
	s->tcp_v4_retrans_segs = v4.tcp_retrans_segs;
	s->tcp_v6_out_rsts = v6.tcp_out_rsts;
	s->tcp_v6_in_segs = v6.tcp_in_segs;
	s->tcp_v6_out_segs = v6.tcp_out_segs;
	s->tcp_v6_retrans_segs = v6.tcp_retrans_segs;

	if (is_offload(adap)) {
		s->frames = usm_stats.frames;
		s->octets = usm_stats.octets;
		s->drops = usm_stats.drops;
		s->rqe_dfr_mod = rdma_stats.rqe_dfr_mod;
		s->rqe_dfr_pkt = rdma_stats.rqe_dfr_pkt;
	}

	s->ofld_no_neigh = err_stats.ofld_no_neigh;
	s->ofld_cong_defer = err_stats.ofld_cong_defer;

	if (!is_t4(adap->params.chip)) {
		int v;

		v = t4_read_reg(adap, SGE_STAT_CFG_A);
		if (STATSOURCE_T5_G(v) == 7) {
			val2 = t4_read_reg(adap, SGE_STAT_MATCH_A);
			val1 = t4_read_reg(adap, SGE_STAT_TOTAL_A);
			s->wc_success = val1 - val2;
			s->wc_fail = val2;
		}
	}
}
