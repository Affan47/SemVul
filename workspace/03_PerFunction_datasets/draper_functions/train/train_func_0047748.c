check_cipher_algo( int algo )
{
    int i;

    do {
       for(i=0; cipher_table[i].name; i++ )
	   if( cipher_table[i].algo == algo ) {
		for(i=0; i < DIM(disabled_algos); i++ ) {
		   if( disabled_algos[i] == algo )
		       return G10ERR_CIPHER_ALGO;
		}
		return 0;
	   }
    } while( load_cipher_modules() );
    return G10ERR_CIPHER_ALGO;
}
