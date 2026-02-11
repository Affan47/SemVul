gdip_pen_setup (GpGraphics *graphics, GpPen *pen)
{
	GpStatus status;
	cairo_matrix_t product;
	double widthx;

	if (!graphics || !pen)
		return InvalidParameter;

	status = gdip_brush_setup (graphics, pen->brush);
	if (status != Ok)
		return status;

	cairo_matrix_init_identity (&product);


	cairo_matrix_multiply (&product, &pen->matrix, graphics->copy_of_ctm);

	if (gdip_near_zero (product.xx) || gdip_near_zero (product.yy)) {

		product.xx = product.yy = 0.0001f;
	}
	cairo_set_matrix (graphics->ct, &product);


	if (pen == graphics->last_pen && !pen->changed)
		return Ok;

	if (pen->width < 1.0) {
		double widthy = 1.0;
		widthx = 1.0;

		cairo_device_to_user_distance (graphics->ct, &widthx, &widthy);
	} else {
		widthx = (double) pen->width;
	}
	cairo_set_line_width (graphics->ct, widthx);

        cairo_set_miter_limit (graphics->ct, (double) pen->miter_limit);
        cairo_set_line_join (graphics->ct, convert_line_join (pen->line_join));
        cairo_set_line_cap (graphics->ct, convert_line_cap (pen));

        if (pen->dash_count > 0) {
                double *dash_array;


                dash_array = convert_dash_array (pen->dash_array, widthx, pen->dash_count);
                cairo_set_dash (graphics->ct, dash_array, pen->dash_count, pen->dash_offset);
                GdipFree (dash_array);
        } else
		cairo_set_dash (graphics->ct, NULL, 0, 0);


	pen->changed = FALSE;
	graphics->last_pen = pen;

	return gdip_get_status (cairo_status (graphics->ct));
}
