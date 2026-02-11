gc_tile(ttip_image_t tile) {
	tiles_to_gc[ntiles_to_gc++] = tile;
	if (ntiles_to_gc == sizeof(tiles_to_gc)/sizeof(tiles_to_gc[0]))
		errx(1, "tile garbage collector overflow");
}
