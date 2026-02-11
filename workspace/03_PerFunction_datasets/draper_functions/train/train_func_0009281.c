tilemapNB2_get_info(int tile_index,int which,const data32_t *tilemap_videoram)
{
	data16_t tile = nth_word32( tilemap_videoram, tile_index );
	int mangle;

	if( namcos2_gametype == NAMCONB2_MACH_BREAKERS )
	{
		mangle = tile;
	}
	else
	{

		mangle = tile&~(0x140);
		if( tile&0x100 ) mangle |= 0x040;
		if( tile&0x040 ) mangle |= 0x100;
	}
	SET_TILE_INFO( NAMCONB1_TILEGFX,mangle,tilemap_palette_bank[which],0)
	tile_info.mask_data = 8*tile + mpMaskData;
}
