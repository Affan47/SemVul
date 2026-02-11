compress_sliced_buf(struct ivtv *itv, u32 line, u8 *buf, u32 size, u8 sav)
{
	u32 line_size = itv->vbi.sliced_decoder_line_size;
	struct v4l2_decode_vbi_line vbi;
	int i;
	unsigned lines = 0;


	for (i = 0; i < size; i++, buf++) {
		if (buf[0] == 0xff && !buf[1] && !buf[2] && buf[3] == sav)
			break;
	}

	size -= i;
	if (size < line_size) {
		return line;
	}
	for (i = 0; i < size / line_size; i++) {
		u8 *p = buf + i * line_size;


		if (p[0] != 0xff || p[1] || p[2] || p[3] != sav) {
			continue;
		}
		vbi.p = p + 4;
		v4l2_subdev_call(itv->sd_video, vbi, decode_vbi_line, &vbi);
		if (vbi.type && !(lines & (1 << vbi.line))) {
			lines |= 1 << vbi.line;
			itv->vbi.sliced_data[line].id = vbi.type;
			itv->vbi.sliced_data[line].field = vbi.is_second_field;
			itv->vbi.sliced_data[line].line = vbi.line;
			memcpy(itv->vbi.sliced_data[line].data, vbi.p, 42);
			line++;
		}
	}
	return line;
}
