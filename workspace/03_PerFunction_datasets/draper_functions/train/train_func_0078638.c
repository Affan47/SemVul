gdip_bitmap_change_rect_pixel_format (BitmapData *srcData, Rect *srcRect, BitmapData *destData, Rect *destRect)
{
	PixelFormat	srcFormat;
	PixelFormat	destFormat;
	StreamingState	srcStream;
	StreamingState	destStream;
	Rect		effectiveDestRect;
	GpStatus	status;

	srcFormat = srcData->pixel_format;
	destFormat = destData->pixel_format;

	if (!gdip_is_pixel_format_conversion_valid (srcFormat, destFormat))
		return InvalidParameter;

	if (!destData->scan0)
		return InvalidParameter;


	if ((destRect->X + destRect->Width > destData->width) || (destRect->Y + destRect->Height > destData->height))
		return InvalidParameter;

	effectiveDestRect = *destRect;

	if (effectiveDestRect.Width > srcRect->Width) {
		effectiveDestRect.Width = srcRect->Width;
	}

	if (effectiveDestRect.Height > srcRect->Height) {
		effectiveDestRect.Height = srcRect->Height;
	}


	status = gdip_init_pixel_stream (&srcStream, srcData, srcRect->X, srcRect->Y, srcRect->Width, srcRect->Height);

	if (status != Ok) {
		return status;
	}

	status = gdip_init_pixel_stream (&destStream, destData, effectiveDestRect.X, effectiveDestRect.Y, effectiveDestRect.Width, effectiveDestRect.Height);

	if (status != Ok) {
		return status;
	}


	if ((srcFormat & PixelFormatIndexed) && !(destFormat & PixelFormatIndexed)) {
		int	pixel;

		while (gdip_pixel_stream_has_next (&srcStream)) {
			pixel = gdip_pixel_stream_get_next (&srcStream);


			pixel = srcData->palette->Entries[pixel];
#if G_BYTE_ORDER != G_LITTLE_ENDIAN
			pixel = GUINT32_FROM_LE (pixel);
#endif
			gdip_pixel_stream_set_next (&destStream, pixel);
		}
	} else {
		if (!gdip_pixel_stream_copy_optimized (&destStream, &srcStream)) {
			while (gdip_pixel_stream_has_next (&srcStream)) {
				gdip_pixel_stream_set_next (&destStream, gdip_pixel_stream_get_next (&srcStream));
			}
		}
	}

	return Ok;
}
