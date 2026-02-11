convert_png(adv_fz* f_in, adv_fz* f_out)
{
	if (adv_png_read_signature(f_in) != 0) {
		throw_png_error();
	}

	if (adv_png_write_signature(f_out, 0) != 0) {
		throw_png_error();
	}

	convert_dat(f_in, f_out, ADV_PNG_CN_IEND);
}
