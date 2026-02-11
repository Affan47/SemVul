update_svr_wgt(int weight, virtual_server_t * vs, real_server_t * rs)
{
	if (weight != rs->weight) {
		log_message(LOG_INFO, "Changing weight from %d to %d for %s service %s of VS %s"
				    , rs->weight
				    , weight
				    , ISALIVE(rs) ? "active" : "inactive"
				    , FMT_RS(rs)
				    , FMT_VS(vs));
		rs->weight = weight;


		if (rs->set && ISALIVE(rs) &&
		    (vs->quorum_state == UP || !vs->s_svr || !ISALIVE(vs->s_svr)))
			ipvs_cmd(LVS_CMD_EDIT_DEST, check_data->vs_group, vs, rs);
		update_quorum_state(vs);
	}
}
