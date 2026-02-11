draw_sat_val_block(cairo_t *cr, double pos_x, double pos_y, double size, double hue){
	cairo_surface_t *surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, ceil(size), ceil(size));
	unsigned char *data = cairo_image_surface_get_data(surface);
	int stride = cairo_image_surface_get_stride(surface);
	int surface_width = cairo_image_surface_get_width(surface);
	int surface_height = cairo_image_surface_get_height(surface);

	Color c;

	unsigned char *line_data;
	for (int y = 0; y < surface_height; ++y){
		line_data = data + stride * y;
		for (int x = 0; x < surface_width; ++x){

			c.hsv.hue = hue;
			c.hsv.saturation = x / size;
			c.hsv.value = y / size;

			color_hsv_to_rgb(&c, &c);

			line_data[2] = c.rgb.red * 255;
			line_data[1] = c.rgb.green * 255;
			line_data[0] = c.rgb.blue * 255;
			line_data[3] = 0xFF;

			line_data += 4;
		}
	}

	cairo_surface_mark_dirty(surface);

	cairo_save(cr);

	cairo_set_source_surface(cr, surface, pos_x - size / 2, pos_y - size / 2);
	cairo_surface_destroy(surface);

	cairo_rectangle(cr, pos_x - size / 2, pos_y - size / 2, size, size);
	cairo_fill(cr);

	cairo_restore(cr);

}
