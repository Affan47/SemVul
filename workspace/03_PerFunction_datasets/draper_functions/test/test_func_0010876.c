_load_events(uint16_t rpc_version, Buf buffer, char *cluster_name,
	     uint32_t rec_cnt)
{
	char *insert = NULL, *format = NULL;
	local_event_t object;
	int i = 0;

	xstrfmtcat(insert, "insert into \"%s_%s\" (%s",
		   cluster_name, event_table, event_req_inx[0]);
	xstrcat(format, "('%s'");
	for(i=1; i<EVENT_REQ_COUNT; i++) {
		xstrfmtcat(insert, ", %s", event_req_inx[i]);
		xstrcat(format, ", '%s'");
	}
	xstrcat(insert, ") values ");
	xstrcat(format, ")");
	for(i=0; i<rec_cnt; i++) {
		memset(&object, 0, sizeof(local_event_t));
		if (_unpack_local_event(&object, rpc_version, buffer)
		    != SLURM_SUCCESS) {
			error("issue unpacking");
			xfree(format);
			xfree(insert);
			break;
		}
		if (i)
			xstrcat(insert, ", ");

		xstrfmtcat(insert, format,
			   object.cluster_nodes,
			   object.cpu_count,
			   object.node_name,
			   object.period_end,
			   object.period_start,
			   object.reason,
			   object.reason_uid,
			   object.state);

	}


	xfree(format);

	return insert;
}
