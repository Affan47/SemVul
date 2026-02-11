draw_layers(struct mame_bitmap *bitmap, const struct rectangle *cliprect, int pri, int layers_ctrl)
{
	data16_t layers_pri = hyprduel_videoregs[0x10/2];
	int layer;
	int offs;
	struct rectangle clip;

	clip.min_x = 0;
	clip.max_x = 319;


	for (layer = 2; layer >= 0; layer--)
	{
		if ( pri == ((layers_pri >> (layer*2)) & 3) )
		{

			data16_t wx = hyprduel_window[layer * 2 + 1];
			data16_t wy = hyprduel_window[layer * 2 + 0];
			wx = wx - (wx & 7);
			wy = wy - (wy & 7);

			if (layers_ctrl & (1<<layer))
			{
				for (offs = cliprect->min_y; offs <= cliprect->max_y; offs++)
				{
					clip.min_y = offs;
					clip.max_y = offs;

					tilemap_set_scrollx(tilemap[layer], 0, hyprduel_scrollx[layer][offs+RASTER_LINES-(LAST_VISIBLE_LINE+1)] - wx);
					tilemap_set_scrolly(tilemap[layer], 0, hyprduel_scrolly[layer][offs+RASTER_LINES-(LAST_VISIBLE_LINE+1)] - wy);
					tilemap_draw(bitmap,&clip,tilemap[layer], 0, 0);
				}
			}
		}
	}
}
