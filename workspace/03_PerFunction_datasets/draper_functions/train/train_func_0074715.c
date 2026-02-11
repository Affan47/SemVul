dump_ies(u8 *buf, u32 buf_len)
{
	u8 *pos = buf;
	u8 id, len;

	while (pos-buf <= buf_len) {
		id = *pos;
		len = *(pos+1);

		DBG_88E("%s ID:%u, LEN:%u\n", __func__, id, len);
		dump_wps_ie(pos, len);

		pos += (2 + len);
	}
}
