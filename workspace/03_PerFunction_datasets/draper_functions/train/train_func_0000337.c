deco16_tilemap_2_draw(struct mame_bitmap *bitmap, const struct rectangle *cliprect, int flags, UINT32 priority)
{
	if (pf2_tilemap_8x8) tilemap_draw(bitmap,cliprect,pf2_tilemap_8x8,flags,priority);
	if (pf2_tilemap_16x16) tilemap_draw(bitmap,cliprect,pf2_tilemap_16x16,flags,priority);
}
