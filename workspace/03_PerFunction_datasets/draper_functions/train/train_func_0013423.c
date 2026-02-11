atarigt_scanline_update(int scanline)
{
	data32_t *base = &atarigen_alpha32[(scanline / 8) * 32 + 24];
	int i;


	if (base >= &atarigen_alpha32[0x400])
		return;


	for (i = 0; i < 8; i++)
	{
		data32_t word = *base++;

		if (word & 0x80000000)
		{
			int newscroll = (word >> 21) & 0x3ff;
			int newbank = (word >> 16) & 0x1f;
			if (newscroll != playfield_xscroll)
			{
				force_partial_update(scanline + i - 1);
				tilemap_set_scrollx(atarigen_playfield_tilemap, 0, newscroll);
				playfield_xscroll = newscroll;
			}
			if (newbank != playfield_color_bank)
			{
				force_partial_update(scanline + i - 1);
				tilemap_set_palette_offset(atarigen_playfield_tilemap, (newbank & 0x1f) << 8);
				playfield_color_bank = newbank;
			}
		}

		if (word & 0x00008000)
		{
			int newscroll = ((word >> 6) - (scanline + i)) & 0x1ff;
			int newbank = word & 15;
			if (newscroll != playfield_yscroll)
			{
				force_partial_update(scanline + i - 1);
				tilemap_set_scrolly(atarigen_playfield_tilemap, 0, newscroll);
				playfield_yscroll = newscroll;
			}
			if (newbank != playfield_tile_bank)
			{
				force_partial_update(scanline + i - 1);
				tilemap_mark_all_tiles_dirty(atarigen_playfield_tilemap);
				playfield_tile_bank = newbank;
			}
		}
	}
}
