GdipGetImageDimension (GpImage *image, float *width, float *height)
{
	if (!image || !width || !height)
		return InvalidParameter;

	switch (image->type) {
	case ImageTypeBitmap:
		*width = image->active_bitmap->width;
		*height = image->active_bitmap->height;
		break;
	case ImageTypeMetafile: {
		MetafileHeader *metaheader = gdip_get_metaheader(image);
		*width = metaheader->Width * METAFILE_DIMENSION_FACTOR / metaheader->DpiX;
		*height = metaheader->Height * METAFILE_DIMENSION_FACTOR / metaheader->DpiY;
		break;
	}
	default:
		return InvalidParameter;
	}
	return Ok;
}
