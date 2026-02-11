expand_colourdata(void)
{
	data8_t *src    = memory_region       ( REGION_GFX3 );
	size_t  srcsize = memory_region_length( REGION_GFX3 );
	int cnt;
	size_t	needed = srcsize / 2 * 3;


	pgm_sprite_a_region_allocate = 1;
	while (pgm_sprite_a_region_allocate < needed)
		pgm_sprite_a_region_allocate = pgm_sprite_a_region_allocate <<1;

	pgm_sprite_a_region = auto_malloc (pgm_sprite_a_region_allocate);


	for (cnt = 0 ; cnt < srcsize/2 ; cnt++)
	{
		data16_t colpack;

		colpack = ((src[cnt*2]) | (src[cnt*2+1] << 8));
		pgm_sprite_a_region[cnt*3+0] = (colpack >> 0 ) & 0x1f;
		pgm_sprite_a_region[cnt*3+1] = (colpack >> 5 ) & 0x1f;
		pgm_sprite_a_region[cnt*3+2] = (colpack >> 10) & 0x1f;
	}
}
