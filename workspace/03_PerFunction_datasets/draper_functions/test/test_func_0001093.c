tds_get_byte(TDSSOCKET * tds)
{
	while (tds->in_pos >= tds->in_len) {
		if (tds_read_packet(tds) < 0)
			return 0;
	}
	return tds->in_buf[tds->in_pos++];
}
