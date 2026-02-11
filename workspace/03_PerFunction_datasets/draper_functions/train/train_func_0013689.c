get_flag_buf(unpack_data_t *unpack_data)
{
	unsigned int flags, new_flags_place, flags_place;

	flags_place = decode_num(unpack_data, rar_getbits(unpack_data), STARTHF2,
				dec_hf2, pos_hf2);
	for (;;) {
		flags = unpack_data->chsetc[flags_place & 0xff];
		unpack_data->flag_buf = flags >> 8;
		new_flags_place = unpack_data->ntoplc[flags++ & 0xff]++;
		if ((flags & 0xff) != 0) {
			break;
		}
		corr_huff(unpack_data, unpack_data->chsetc, unpack_data->ntoplc);
	}
	unpack_data->chsetc[flags_place & 0xff] = unpack_data->chsetc[new_flags_place & 0xff];
	unpack_data->chsetc[new_flags_place & 0xff] = flags;
}
