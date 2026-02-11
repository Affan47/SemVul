draw_sprites( struct mame_bitmap *bitmap, const struct rectangle *cliprect )
{
	const UINT8 *source, *finish;

	finish = spriteram;
	source = spriteram+0x200;
	while( source>finish ){
		source -= 8;
		draw_sprite( source, bitmap,cliprect );
	}
}
