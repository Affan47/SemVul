perform_svr_state(int alive, virtual_server_t * vs, real_server_t * rs)
{


	if (!ISALIVE(rs) && alive) {
		log_message(LOG_INFO, "%s service %s to VS %s"
				    , (rs->inhibit) ? "Enabling" : "Adding"
				    , FMT_RS(rs)
				    , FMT_VS(vs));

		if (vs->quorum_state == UP || !vs->s_svr || !ISALIVE(vs->s_svr)) {
			ipvs_cmd(LVS_CMD_ADD_DEST, check_data->vs_group, vs, rs);
		}
		rs->alive = alive;
		if (rs->notify_up) {
			log_message(LOG_INFO, "Executing [%s] for service %s in VS %s"
					    , rs->notify_up
					    , FMT_RS(rs)
					    , FMT_VS(vs));
			notify_exec(rs->notify_up);
		}
#ifdef _WITH_SNMP_
		check_snmp_rs_trap(rs, vs);
#endif


		update_quorum_state(vs);
	}

	if (ISALIVE(rs) && !alive) {
		log_message(LOG_INFO, "%s service %s from VS %s"
				    , (rs->inhibit) ? "Disabling" : "Removing"
				    , FMT_RS(rs)
				    , FMT_VS(vs));


		if (vs->quorum_state == UP || !vs->s_svr || !ISALIVE(vs->s_svr)) {
			ipvs_cmd(LVS_CMD_DEL_DEST, check_data->vs_group, vs, rs);
		}
		rs->alive = alive;
		if (rs->notify_down) {
			log_message(LOG_INFO, "Executing [%s] for service %s in VS %s"
					    , rs->notify_down
					    , FMT_RS(rs)
					    , FMT_VS(vs));
			notify_exec(rs->notify_down);
		}
#ifdef _WITH_SNMP_
		check_snmp_rs_trap(rs, vs);
#endif


		update_quorum_state(vs);
	}
}
