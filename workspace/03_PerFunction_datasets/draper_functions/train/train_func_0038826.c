K054157_get_tile_info(int tile_index,int layer)
{
	data16_t *addr;
	int attr, code;
	data16_t *lbase = K054157_rambase + 0x2000*layer;
	if(tile_index < 64*32)
		addr = lbase + (tile_index<<1);
	else
		addr = lbase + (tile_index<<1) + 0x1000 - 64*32*2;

	attr = addr[0];
	code = addr[1];
	tile_info.flags = 0;

	(*K054157_callback)(layer, &code, &attr);
	SET_TILE_INFO(K054157_gfxnum,
			code,
			attr,
			tile_info.flags)
}
