image_zoom_get_default(ImageWindow *imd)
{
	gdouble zoom = 1.0;

	switch (options->image.zoom_mode)
	{
	case ZOOM_RESET_ORIGINAL:
		break;
	case ZOOM_RESET_FIT_WINDOW:
		zoom = 0.0;
		break;
	case ZOOM_RESET_NONE:
		if (imd) zoom = image_zoom_get(imd);
		break;
	}

	return zoom;
}
