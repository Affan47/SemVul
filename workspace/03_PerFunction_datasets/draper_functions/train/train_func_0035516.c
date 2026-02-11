mark_bg_tile_dirty(offs_t offset)
{
	if (offset & 0x80)
		tilemap_mark_tile_dirty( bg_tilemap_r, offset );
	else
		tilemap_mark_tile_dirty( bg_tilemap_l, offset );
}
