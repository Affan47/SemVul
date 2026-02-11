get_bg_tile_info(int tile_index)
{
	int attr = bionicc_bgvideoram[2*tile_index+1];
	SET_TILE_INFO(
			1,
			(bionicc_bgvideoram[2*tile_index] & 0xff) + ((attr & 0x07) << 8),
			(attr & 0x18) >> 3,
			TILE_FLIPXY((attr & 0xc0) >> 6))
}
