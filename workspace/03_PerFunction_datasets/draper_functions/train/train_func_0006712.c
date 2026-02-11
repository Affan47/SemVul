decode_libjpeg_h_samp2(struct v4lconvert_data *data,
	unsigned char *ydest, unsigned char *udest, unsigned char *vdest,
	int v_samp)
{
	struct jpeg_decompress_struct *cinfo = &data->cinfo;
	int y;
	unsigned int width = cinfo->image_width;
	JSAMPROW y_rows[16], u_rows[8], v_rows[8];
	JSAMPARRAY rows[3] = { y_rows, u_rows, v_rows };

	while (cinfo->output_scanline < cinfo->image_height) {
		for (y = 0; y < 8 * v_samp; y++) {
			y_rows[y] = ydest;
			ydest += width;
		}
		for (y = 0; y < 8; y++) {
			u_rows[y] = udest;
			v_rows[y] = vdest;
			udest += width / 2;
			vdest += width / 2;
		}
		y = jpeg_read_raw_data(cinfo, rows, 8 * v_samp);
		if (y != 8 * v_samp)
			return -1;


		if (cinfo->output_scanline % 16) {
			udest -= width * 8 / 2;
			vdest -= width * 8 / 2;
		}
	}
	return 0;
}
