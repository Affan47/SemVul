select_g_pack_select_info(time_t last_query_time,
				     uint16_t show_flags, Buf *buffer,
				     uint16_t protocol_version)
{
	if (slurm_select_init(0) < 0)
		return SLURM_ERROR;

	return (*(ops[select_context_default].pack_select_info))
		(last_query_time, show_flags, buffer, protocol_version);
}
