GdipCreateImageAttributes (GpImageAttributes **imageattr)
{
	GpImageAttributes *result;

	if (!imageattr)
		return InvalidParameter;

	result = (GpImageAttributes *) GdipAlloc (sizeof (GpImageAttributes));
	if (!result) {
		*imageattr = NULL;
		return OutOfMemory;
	}

	gdip_init_image_attribute (&result->def);
	gdip_init_image_attribute (&result->bitmap);
	gdip_init_image_attribute (&result->brush);
	gdip_init_image_attribute (&result->pen);
	gdip_init_image_attribute (&result->text);
	result->color = 0;
	result->wrapmode = WrapModeClamp;

	*imageattr = result;
	return Ok;
}
