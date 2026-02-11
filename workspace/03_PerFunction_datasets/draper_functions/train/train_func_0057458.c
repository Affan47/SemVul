write_image(adv_fz* f, unsigned pix_width, unsigned pix_height, unsigned pix_pixel, unsigned char* pix_ptr, unsigned pix_scanline, unsigned char* pal_ptr, unsigned pal_size, unsigned char* rns_ptr, unsigned rns_size)
{
	if (pix_pixel == 1) {
		png_write(f, pix_width, pix_height, pix_pixel, pix_ptr, pix_scanline, pal_ptr, pal_size, rns_ptr, rns_size, opt_level);
	} else {
		unsigned char new_pal_ptr[256*3];
		unsigned new_pal_count;
		unsigned char new_rns_ptr[256];
		unsigned new_rns_count;
		unsigned char* new_ptr;
		unsigned new_scanline;

		new_ptr = 0;

		try {
			if (pix_pixel == 3
				&& reduce_image(&new_ptr, &new_scanline, new_pal_ptr, &new_pal_count, new_rns_ptr, &new_rns_count, pix_width, pix_height, pix_ptr, pix_scanline, rns_ptr, rns_size)) {
				png_write(f, pix_width, pix_height, 1, new_ptr, new_scanline, new_pal_ptr, new_pal_count * 3, new_rns_count ? new_rns_ptr : 0, new_rns_count, opt_level);
			} else {
				png_write(f, pix_width, pix_height, pix_pixel, pix_ptr, pix_scanline, 0, 0, rns_ptr, rns_size, opt_level);
			}
		} catch (...) {
			data_free(new_ptr);
			throw;
		}

		data_free(new_ptr);
	}
}
