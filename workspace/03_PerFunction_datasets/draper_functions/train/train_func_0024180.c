tds_peek(TDSSOCKET * tds)
{
	unsigned char result = tds_get_byte(tds);
	if (tds->in_pos > 0)
		--tds->in_pos;
	return result;
}
