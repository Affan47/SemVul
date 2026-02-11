load_line_YUV420SP(u8 *src_bits, u32 x_offset, u32 y_offset, u32 y_pitch, u32 width, u32 height, u8 *dst_bits)
{
	s32 frameSize = width * height;
	s32 j, yp, uvp, y, y1192, r, g, b, u, v;
	u32 i;

	yp = (s32)(x_offset + y_offset * y_pitch / 1.5f);
	j = y_offset;

	uvp = frameSize + (j >> 1) * width, u = 0, v = 0;

	for (i=0; i<width; i++, yp++) {

		y = (0xff & ((int) src_bits[yp])) - 16;
		if (y < 0) y = 0;
		if ((i & 1) == 0)
		{
			v = (0xff & src_bits[uvp++]) - 128;
			u = (0xff & src_bits[uvp++]) - 128;
		}

		y1192 = 1192 * y;
		r = (y1192 + 1634 * v);
		g = (y1192 - 833 * v - 400 * u);
		b = (y1192 + 2066 * u);

		if (r < 0)
			r = 0;
		else if (r > 262143)
			r = 262143;
		if (g < 0)
			g = 0;
		else if (g > 262143)
			g = 262143;
		if (b < 0)
			b = 0;
		else if (b > 262143)
			b = 262143;

		*((u32*)dst_bits) = 0xff000000 | ((b << 6) & 0xff0000)
					| ((g >> 2) & 0xff00) | ((r >> 10) & 0xff);
		dst_bits+=4;
	}
}
