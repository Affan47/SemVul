turn_report_allocation_delete(void *a)
{
	if(a) {
		ts_ur_super_session *ss = (ts_ur_super_session*)(((allocation*)a)->owner);
		if(ss) {
			turn_turnserver *server = (turn_turnserver*)ss->server;
			if(server) {
				ioa_engine_handle e = turn_server_get_engine(server);
				if(e && e->verbose) {
					TURN_LOG_FUNC(TURN_LOG_LEVEL_INFO,"session %018llu: delete: realm=<%s>, username=<%s>\n", (unsigned long long)ss->id, (char*)ss->realm_options.name, (char*)ss->username);
				}
#if !defined(TURN_NO_HIREDIS)
				{
					char key[1024];
					if(ss->realm_options.name[0]) {
						snprintf(key,sizeof(key),"turn/realm/%s/user/%s/allocation/%018llu/status",ss->realm_options.name,(char*)ss->username, (unsigned long long)ss->id);
					} else {
						snprintf(key,sizeof(key),"turn/user/%s/allocation/%018llu/status",(char*)ss->username, (unsigned long long)ss->id);
					}
					send_message_to_redis(e->rch, "del", key, "");
					send_message_to_redis(e->rch, "publish", key, "deleted");
				}
#endif
			}
		}
	}
}
