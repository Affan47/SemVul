jobacctinfo_pack(jobacctinfo_t *jobacct,
			     uint16_t rpc_version, uint16_t protocol_type,
			     Buf buffer)
{
	int i = 0;

	if (!plugin_polling && (protocol_type != PROTOCOL_TYPE_DBD))
		return;


	if (protocol_type == PROTOCOL_TYPE_DBD)
		rpc_version = slurmdbd_translate_rpc(rpc_version);


	if (!jobacct || (jobacct->min_cpu == NO_VAL)) {
		for (i = 0; i < 12; i++)
			pack32((uint32_t)NO_VAL, buffer);
		for (i = 0; i < 4; i++)
			_pack_jobacct_id(NULL, rpc_version, buffer);
		return;
	}

	pack32((uint32_t)jobacct->user_cpu_sec, buffer);
	pack32((uint32_t)jobacct->user_cpu_usec, buffer);
	pack32((uint32_t)jobacct->sys_cpu_sec, buffer);
	pack32((uint32_t)jobacct->sys_cpu_usec, buffer);
	pack32((uint32_t)jobacct->max_vsize, buffer);
	pack32((uint32_t)jobacct->tot_vsize, buffer);
	pack32((uint32_t)jobacct->max_rss, buffer);
	pack32((uint32_t)jobacct->tot_rss, buffer);
	pack32((uint32_t)jobacct->max_pages, buffer);
	pack32((uint32_t)jobacct->tot_pages, buffer);
	pack32((uint32_t)jobacct->min_cpu, buffer);
	pack32((uint32_t)jobacct->tot_cpu, buffer);

	_pack_jobacct_id(&jobacct->max_vsize_id, rpc_version, buffer);
	_pack_jobacct_id(&jobacct->max_rss_id, rpc_version, buffer);
	_pack_jobacct_id(&jobacct->max_pages_id, rpc_version, buffer);
	_pack_jobacct_id(&jobacct->min_cpu_id, rpc_version, buffer);
}
