draw_pixel(int x, int y, const CL_Color &color)
{
	lock();

	cl_uint8* buf = static_cast<cl_uint8*>(impl->get_data());
	CL_PixelFormat format = get_format();

	if (format.get_type() == pixelformat_index)
	{
		throw CL_Error("Direct settings of CL_Colors pixels in paletted mode is not supported.");
	}
	else if (format.get_type() == pixelformat_rgba)
	{
		int depth = format.get_depth ();
		int bytes_per_pixel = (depth + 7)/8;
		cl_uint8 *pos = &buf[y * impl->pitch + x * bytes_per_pixel];

		int red_shift = format.get_mask_shift(format.get_red_mask()),
			green_shift = format.get_mask_shift(format.get_green_mask()),
			blue_shift = format.get_mask_shift(format.get_blue_mask()),
			alpha_shift = format.get_mask_shift(format.get_alpha_mask());

		switch (bytes_per_pixel)
		{
		case 4:
		case 3:
			{
				cl_uint32 c = (color.get_red() << red_shift) | (color.get_green() << green_shift) | (color.get_blue() << blue_shift) | (color.get_alpha() << alpha_shift);
				memcpy (pos, &c, bytes_per_pixel);
			}
			break;

		case 2:
			{
				cl_uint16 c = (color.get_red() << red_shift) | (color.get_green() << green_shift) | (color.get_blue() << blue_shift) | (color.get_alpha() << alpha_shift);
				memcpy (pos, &c, bytes_per_pixel);
			}
			break;

		case 1:
			{
				cl_uint8 c = (color.get_red() << red_shift) | (color.get_green() << green_shift) | (color.get_blue() << blue_shift) | (color.get_alpha() << alpha_shift);
				*pos = c;
			}
			break;

		default:
			throw CL_Error("Unsuported pixel format depth for draw_pixel.");
		}

	}
	unlock();
}
