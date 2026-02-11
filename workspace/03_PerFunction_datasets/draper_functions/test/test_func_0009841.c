update_read_create_offscreen_bitmap_order(STREAM* s, CREATE_OFFSCREEN_BITMAP_ORDER* create_offscreen_bitmap)
{
	uint16 flags;
	boolean deleteListPresent;

	stream_read_uint16(s, flags);
	create_offscreen_bitmap->id = flags & 0x7FFF;
	deleteListPresent = (flags & 0x8000) ? True : False;

	stream_read_uint16(s, create_offscreen_bitmap->cx);
	stream_read_uint16(s, create_offscreen_bitmap->cy);

	if (deleteListPresent)
	{
		int i;
		OFFSCREEN_DELETE_LIST* deleteList;

		deleteList = &(create_offscreen_bitmap->deleteList);

		stream_read_uint16(s, deleteList->cIndices);

		if (deleteList->indices == NULL)
			deleteList->indices = xmalloc(deleteList->cIndices * 2);
		else
			deleteList->indices = xrealloc(deleteList->indices, deleteList->cIndices * 2);

		for (i = 0; i < deleteList->cIndices; i++)
		{
			stream_read_uint16(s, deleteList->indices[i]);
		}
	}
}
