update_read_bitmap(rdpUpdate* update, STREAM* s, BITMAP_UPDATE* bitmap_update)
{
	int i;

	stream_read_uint16(s, bitmap_update->number);

	bitmap_update->bitmaps = (BITMAP_DATA*) xzalloc(sizeof(BITMAP_DATA) * bitmap_update->number);


	for (i = 0; i < bitmap_update->number; i++)
	{
		update_read_bitmap_data(s, &bitmap_update->bitmaps[i]);
	}
}
