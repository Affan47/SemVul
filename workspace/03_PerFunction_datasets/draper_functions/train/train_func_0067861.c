get_gumbo_fg_tile_info(int tile_index)
{
	int tileno;
	tileno = gumbo_fg_videoram[tile_index];
	SET_TILE_INFO(1,tileno,1,0)
}
