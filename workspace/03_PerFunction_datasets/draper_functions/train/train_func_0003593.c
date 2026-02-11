gfire_file_chunk_set_checksum(gfire_file_chunk *p_chunk, const gchar *p_checksum)
{
	if(!p_chunk || !p_checksum)
		return;

	if(p_chunk->checksum)
		g_free(p_chunk->checksum);

	p_chunk->checksum = g_strdup(p_checksum);

	if(p_chunk->data_packets_received == p_chunk->data_packet_count)
	{

		if(!gfire_file_chunk_check_checksum(p_chunk))
		{
			purple_debug_warning("gfire", "P2P: bad checksum for chunk at offset %lu\n", p_chunk->offset);
			gfire_file_chunk_init(p_chunk, p_chunk->offset, p_chunk->size);
			gfire_file_chunk_start_transfer(p_chunk);
			return;
		}

		if(p_chunk->done_func)
			(*p_chunk->done_func)(p_chunk->user_data);
	}
}
