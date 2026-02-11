draw_sprites(struct mame_bitmap* bitmap, const struct rectangle* cliprect)
{
	int i;

	for (i = 0; i < 14; i++)
	{
		int code = (starshp1_obj_ram[i] & 0xf) ^ 0xf;

		drawgfx(bitmap, Machine->gfx[1],
			code % 8,
			code / 8,
			0, 0,
			get_sprite_hpos(i),
			get_sprite_vpos(i),
			cliprect, TRANSPARENCY_PEN, 0);
	}
}
