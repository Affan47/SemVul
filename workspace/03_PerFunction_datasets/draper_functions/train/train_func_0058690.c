DrawSpriteInit( void )
{
	int i;

	for(i = 0;i <= 253;i++)
	{
		gfx_drawmode_table[i] = DRAWMODE_SOURCE;
	}
	gfx_drawmode_table[254] = DRAWMODE_SHADOW;
	gfx_drawmode_table[255] = DRAWMODE_NONE;
	for( i = 0; i<16*256; i++ )
	{
		palette_shadow_table[i] = i+0x2000;
	}
}
