K054157_change_tilemap(int layer)
{
	int flip = 0;
	if(K054157_regs[8|layer] & 1) {
		tilemap_set_enable(K054157_tilemapb[layer], 1);
		tilemap_set_enable(K054157_tilemaps[layer], 0);
		K054157_tilemap[layer] = K054157_tilemapb[layer];
	} else {
		tilemap_set_enable(K054157_tilemapb[layer], 0);
		tilemap_set_enable(K054157_tilemaps[layer], 1);
		K054157_tilemap[layer] = K054157_tilemaps[layer];
	}
	tilemap_mark_all_tiles_dirty(K054157_tilemap[layer]);

	if(K054157_regs[0] & 0x20)
		flip |= TILEMAP_FLIPY;
	if(K054157_regs[0] & 0x10)
		flip |= TILEMAP_FLIPX;

	tilemap_set_flip(K054157_tilemap[layer], flip);

	K054157_reset_linescroll();
}
