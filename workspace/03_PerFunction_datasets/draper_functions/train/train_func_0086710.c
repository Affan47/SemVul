checkGammaSettings( Plustek_Scanner *s )
{
	int i, j;

	for( i = 0; i < 4 ; i++ ) {
		for( j = 0; j < s->gamma_length; j++ ) {
			if( s->gamma_table[i][j] > s->gamma_range.max ) {
				s->gamma_table[i][j] = s->gamma_range.max;
			}
		}
	}
}
