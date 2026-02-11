build_mode_page(uint8_t *data, struct mode_pg *pg,
			   uint8_t pc, uint16_t *alloc_len)
{
	uint8_t *p;
	int len;
	uint8_t *mode_data;

	len = pg->pcode_size;
	if (*alloc_len >= 2) {
		data[0] = pg->pcode;
		data[1] = len;
	}
	*alloc_len -= min_t(uint16_t, *alloc_len, 2);

	p = &data[2];
	len += 2;
	if (*alloc_len >= pg->pcode_size) {
		if (pc == 1)
			mode_data = pg->mode_data + pg->pcode_size;
		else
			mode_data = pg->mode_data;

		memcpy(p, mode_data, pg->pcode_size);
	}

	*alloc_len -= min_t(uint16_t, *alloc_len, pg->pcode_size);

	return len;
}
