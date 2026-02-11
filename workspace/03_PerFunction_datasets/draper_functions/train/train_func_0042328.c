get_sprcros2_fgtile_info(int tile_index)
{
	unsigned int tile_number = sprcros2_fgvideoram[tile_index];
	unsigned char attr = sprcros2_fgvideoram[tile_index+0x400];


	tile_number += (attr&0x03)<<8;

	SET_TILE_INFO(
			2,
			tile_number,
			(attr&0xfc)>>2,
			0)
}
