rt_tile_is_visible(RendererTiles *rt, ImageTile *it)
{
	PixbufRenderer *pr = rt->pr;
	return (it->x + it->w >= rt->x_scroll && it->x < rt->x_scroll + pr->vis_width &&
		it->y + it->h >= rt->y_scroll && it->y < rt->y_scroll + pr->vis_height);
}
