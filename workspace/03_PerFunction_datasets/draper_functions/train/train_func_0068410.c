set_fg_page(int page,int value)
{
	int tile_index;

	if (fg_page[page] != value)
	{
		fg_page[page] = value;
		for (tile_index = page * 0x800;tile_index < (page+1)*0x800;tile_index++)
			tilemap_mark_tile_dirty(fg_tilemap,tile_index);
	}
}
