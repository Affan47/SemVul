get_dbz2_bg_tile_info(int tile_index)
{
	int tileno, colour, flipx;

	tileno = dbz2_bg_videoram[tile_index*2+1] & 0x7fff;


	colour = (dbz2_bg_videoram[tile_index*2] & 0x000f);

	flipx = (dbz2_bg_videoram[tile_index*2] & 0x0080) >> 7;

	SET_TILE_INFO(1,tileno,colour,TILE_FLIPYX(flipx))
}
