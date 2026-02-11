graph_setpixel(struct graph* g, int x, int y, int color)
{
	if(g == NULL || color >= 256)
		return;
	if(x < 0) x = 0;
	if(y < 0) y = 0;
	if(x >= g->width)  { x = g->width  - 1; }
	if(y >= g->height) { y = g->height - 1; }
	if(color >= g->pallet_count) { graph_pallet(g,color,graph_rgb(0,0,0)); }

	g->raw_data[y * (g->width + 1) + x + 1] = (unsigned char)color;
	g->png_dirty = 1;

	return;
}
