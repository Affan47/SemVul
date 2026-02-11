draw_layer(struct mame_bitmap *bitmap,const struct rectangle *cliprect,
		struct tilemap *tilemap,int *scrollx,int *scrolly,int priority)
{
	int start,i;

	struct rectangle clip;

	clip.min_x = cliprect->min_x;
	clip.max_x = cliprect->max_x;
	start = cliprect->min_y - 128;
	do
	{
		i = start;
		while (scrollx[i+1] == scrollx[start] && scrolly[i+1] == scrolly[start]
				&& i < Machine->visible_area.max_y - 128)
			i++;

		clip.min_y = start + 128;
		clip.max_y = i + 128;
		sect_rect(&clip,cliprect);
		tilemap_set_scrollx(tilemap,0,scrollx[start] + xadjust);
		tilemap_set_scrolly(tilemap,0,scrolly[start]);
		tilemap_draw(bitmap,&clip,tilemap,priority,0);

		start = i+1;
	} while (start < cliprect->max_y - 128);
}
