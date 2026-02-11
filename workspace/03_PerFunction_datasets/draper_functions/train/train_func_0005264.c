sshangha_tilemap_draw(struct mame_bitmap *bitmap)
{
	const struct mame_bitmap *bitmap0 = tilemap_get_pixmap(pf1_16x16_tilemap);
	const struct mame_bitmap *bitmap1 = tilemap_get_pixmap(pf2_tilemap);
	int x,y,p;

	for (y=0; y<240; y++) {
		for (x=0; x<320; x++) {
			p=(((UINT16*)bitmap0->line[y])[x])&0xf;
			p|=((((UINT16*)bitmap1->line[y])[x])&0xf)<<4;

			plot_pixel(bitmap, x, y, Machine->pens[p|0x300]);
		}
	}
}
