drawsprite_16x64( struct mame_bitmap *bitmap, const struct rectangle *cliprect, int code,
							  int sx, int sy, int bank, int flags ) {
	if ( bank & 2 ) {
		WC90_DRAW_SPRITE( code+3, sx, sy+48 );
		WC90_DRAW_SPRITE( code+2, sx, sy+32 );
		WC90_DRAW_SPRITE( code+1, sx, sy+16 );
		WC90_DRAW_SPRITE( code, sx, sy );
	} else {
		WC90_DRAW_SPRITE( code, sx, sy );
		WC90_DRAW_SPRITE( code+1, sx, sy+16 );
		WC90_DRAW_SPRITE( code+2, sx, sy+32 );
		WC90_DRAW_SPRITE( code+3, sx, sy+48 );
	}
}
