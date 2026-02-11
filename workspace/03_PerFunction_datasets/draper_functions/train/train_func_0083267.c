normalize_thumb (int *width,
		 int *height,
		 int  max_size,
		 int  cache_max_size)
{
	gboolean modified;
	float    max_w = max_size;
	float    max_h = max_size;
	float    w = *width;
	float    h = *height;
	float    factor;
	int      new_width, new_height;

	if (max_size > cache_max_size) {
		if ((*width < cache_max_size - 1) && (*height < cache_max_size - 1))
			return FALSE;
	}
	else if ((*width < max_size - 1) && (*height < max_size - 1))
		return FALSE;

	factor = MIN (max_w / w, max_h / h);
	new_width  = MAX ((int) (w * factor), 1);
	new_height = MAX ((int) (h * factor), 1);

	modified = (new_width != *width) || (new_height != *height);

	*width = new_width;
	*height = new_height;

	return modified;
}
