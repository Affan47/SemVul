get_tile_info(int tile_index)
{
	unsigned char attr = suprloco_videoram[2*tile_index+1];
	SET_TILE_INFO(
			0,
			suprloco_videoram[2*tile_index] | ((attr & 0x03) << 8),
			(attr & 0x1c) >> 2,
			0)
	tile_info.priority = (attr & 0x20) >> 5;
}
