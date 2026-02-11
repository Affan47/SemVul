gdip_bitmap_new_with_frame (const GUID *dimension, BOOL add_bitmapdata)
{
	GpBitmap	*result;
	FrameData	*frame;

	if (dimension == NULL) {
		dimension = &gdip_image_frameDimension_page_guid;
	}

	result = gdip_bitmap_new();
	if (result != NULL) {
		frame = gdip_frame_add(result, dimension);
		if ((frame != NULL) && add_bitmapdata) {
			BitmapData	*bitmap_data;

			bitmap_data = gdip_frame_add_bitmapdata(frame);
			if (bitmap_data != NULL) {
				result->active_bitmap = bitmap_data;
			}
		}
	}
	return result;
}
