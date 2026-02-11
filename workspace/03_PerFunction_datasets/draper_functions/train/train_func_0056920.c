exec_resize (GthAsyncTask *task,
	     gpointer      user_data)
{
	ResizeData      *resize_data = user_data;
	cairo_surface_t *source;
	cairo_surface_t *destination;
	int              w, h;
	int              new_w, new_h;
	int              max_w, max_h;
	GthImage        *destination_image;

	source = gth_image_get_cairo_surface (gth_image_task_get_source (GTH_IMAGE_TASK (task)));
	w = cairo_image_surface_get_width (source);
	h = cairo_image_surface_get_height (source);

	if (resize_data->allow_swap
	    && (((h > w) && (resize_data->width > resize_data->height))
		|| ((h < w) && (resize_data->width < resize_data->height))))
	{
		max_w = resize_data->height;
		max_h = resize_data->width;
	}
	else {
		max_w = resize_data->width;
		max_h = resize_data->height;
	}

	if (resize_data->unit == GTH_UNIT_PERCENTAGE) {
		new_w = w * ((double) max_w / 100.0);
		new_h = h * ((double) max_h / 100.0);
	}
	else if (resize_data->keep_aspect_ratio) {
		new_w = w;
		new_h = h;
		scale_keeping_ratio (&new_w, &new_h, max_w, max_h, TRUE);
	}
	else {
		new_w = max_w;
		new_h = max_h;
	}

	if ((new_w > 1) && (new_h > 1))
		destination = _cairo_image_surface_scale (source, new_w, new_h, SCALE_FILTER_BEST, task);
	else
		destination = NULL;
	destination_image = gth_image_new_for_surface (destination);
	gth_image_task_set_destination (GTH_IMAGE_TASK (task), destination_image);

	_g_object_unref (destination_image);
	cairo_surface_destroy (destination);
	cairo_surface_destroy (source);

	return NULL;
}
