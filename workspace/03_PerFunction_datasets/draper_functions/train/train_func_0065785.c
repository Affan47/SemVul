update_read_bitmap_data(STREAM* s, BITMAP_DATA* bitmap_data)
{
	uint8* srcData;
	uint16 dstSize;
	boolean status;
	uint16 bytesPerPixel;

	stream_read_uint16(s, bitmap_data->left);
	stream_read_uint16(s, bitmap_data->top);
	stream_read_uint16(s, bitmap_data->right);
	stream_read_uint16(s, bitmap_data->bottom);
	stream_read_uint16(s, bitmap_data->width);
	stream_read_uint16(s, bitmap_data->height);
	stream_read_uint16(s, bitmap_data->bpp);
	stream_read_uint16(s, bitmap_data->flags);
	stream_read_uint16(s, bitmap_data->length);

	bytesPerPixel = (bitmap_data->bpp + 7) / 8;

	if (bitmap_data->flags & BITMAP_COMPRESSION)
	{
		uint16 cbCompMainBodySize;
		uint16 cbUncompressedSize;

		stream_seek_uint16(s);
		stream_read_uint16(s, cbCompMainBodySize);
		stream_seek_uint16(s);
		stream_read_uint16(s, cbUncompressedSize);

		dstSize = cbUncompressedSize;
		bitmap_data->length = cbCompMainBodySize;

		bitmap_data->data = (uint8*) xzalloc(dstSize);

		stream_get_mark(s, srcData);
		stream_seek(s, bitmap_data->length);

		status = bitmap_decompress(srcData, bitmap_data->data, bitmap_data->width, bitmap_data->height,
				bitmap_data->length, bitmap_data->bpp, bitmap_data->bpp);

		if (status != True)
			printf("bitmap decompression failed, bpp:%d\n", bitmap_data->bpp);
	}
	else
	{
		stream_get_mark(s, srcData);
		dstSize = bitmap_data->length;
		stream_seek(s, bitmap_data->length);
		bitmap_data->data = (uint8*) xzalloc(dstSize);
		memcpy(bitmap_data->data, srcData, dstSize);
	}
}
