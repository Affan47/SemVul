update_read_stream_bitmap_first_order(STREAM* s, STREAM_BITMAP_FIRST_ORDER* stream_bitmap_first)
{
	stream_read_uint8(s, stream_bitmap_first->bitmapFlags);
	stream_read_uint8(s, stream_bitmap_first->bitmapBpp);
	stream_read_uint16(s, stream_bitmap_first->bitmapType);
	stream_read_uint16(s, stream_bitmap_first->bitmapWidth);
	stream_read_uint16(s, stream_bitmap_first->bitmapHeight);

	if (stream_bitmap_first->bitmapFlags & STREAM_BITMAP_V2)
		stream_read_uint32(s, stream_bitmap_first->bitmapSize);
	else
		stream_read_uint16(s, stream_bitmap_first->bitmapSize);

	stream_read_uint16(s, stream_bitmap_first->bitmapBlockSize);
	stream_seek(s, stream_bitmap_first->bitmapBlockSize);
}
