GdipDrawImage (GpGraphics *graphics, GpImage *image, float x, float y)
{
	if (!image)
		return InvalidParameter;

	switch (image->type) {
	case ImageTypeBitmap: {
		BitmapData *data = image->active_bitmap;
		return GdipDrawImageRect (graphics, image, x, y, data->width, data->height);
	}
	case ImageTypeMetafile: {
		MetafileHeader *metaheader = &((GpMetafile*)image)->metafile_header;
		return GdipDrawImageRect (graphics, image, x, y, metaheader->Width, metaheader->Height);
	}
	default:
		return InvalidParameter;
	}
}
