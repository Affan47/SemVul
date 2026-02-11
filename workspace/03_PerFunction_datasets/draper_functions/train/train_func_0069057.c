cps1_render_layer(struct mame_bitmap *bitmap,const struct rectangle *cliprect,int layer,int primask)
{
	switch (layer)
	{
		case 0:
			cps1_render_sprites(bitmap,cliprect);
			break;
		case 1:
		case 2:
		case 3:
			tilemap_draw(bitmap,cliprect,tilemap[layer-1],TILEMAP_BACK,primask);
			break;
	}
}
