update_read_cache_bitmap_v3_order(STREAM* s, CACHE_BITMAP_V3_ORDER* cache_bitmap_v3_order, boolean compressed, uint16 flags)
{
	uint32 bitmapLength;
	uint8 bitsPerPixelId;
	BITMAP_DATA_EX* bitmapData;

	cache_bitmap_v3_order->cacheId = flags & 0x00000003;
	cache_bitmap_v3_order->flags = (flags & 0x0000FF80) >> 7;

	bitsPerPixelId = (flags & 0x00000078) >> 3;
	cache_bitmap_v3_order->bpp = CBR23_BPP[bitsPerPixelId];

	stream_read_uint16(s, cache_bitmap_v3_order->cacheIndex);
	stream_read_uint32(s, cache_bitmap_v3_order->key1);
	stream_read_uint32(s, cache_bitmap_v3_order->key2);

	bitmapData = &cache_bitmap_v3_order->bitmapData;

	stream_read_uint8(s, bitmapData->bpp);
	stream_seek_uint8(s);
	stream_seek_uint8(s);
	stream_read_uint8(s, bitmapData->codecID);
	stream_read_uint16(s, bitmapData->width);
	stream_read_uint16(s, bitmapData->height);
	stream_read_uint32(s, bitmapData->length);

	if (bitmapData->data == NULL)
		bitmapData->data = (uint8*) xmalloc(bitmapData->length);
	else
		bitmapData->data = (uint8*) xrealloc(bitmapData->data, bitmapData->length);

	stream_read(s, bitmapData->data, bitmapData->length);
}
