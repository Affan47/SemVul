IMAGE_take(GB_IMG *img, GB_IMG_OWNER *owner, void *owner_handle, int width, int height, unsigned char *data)
{
	if (!img)
		return;


	if (img->owner == owner && img->owner_handle == owner_handle)
		return;


	(*img->owner->free)(img, img->owner_handle);


	if (img->temp_owner == img->owner)
	{
		img->temp_owner = NULL;
		img->temp_handle = 0;
	}


	img->owner = owner;
	img->owner_handle = owner_handle;


	IMAGE_check(img, NULL);
	img->temp_owner = owner;
	img->temp_handle = owner_handle;


	img->width = width;
	img->height = height;
	img->data = data;
	if (owner && owner->format)
		img->format = owner->format;
	img->is_void = width <= 0 || height <= 0;
}
