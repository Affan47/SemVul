output( Blip_Buffer* center, Blip_Buffer* left, Blip_Buffer* right )
{
	for ( int i = 0; i < osc_count; i++ )
		osc_output( i, center, left, right );
}
