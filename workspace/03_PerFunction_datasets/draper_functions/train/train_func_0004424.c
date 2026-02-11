pubkey_get_nskey( int algo )
{
    int i;
    do {
	for(i=0; pubkey_table[i].name; i++ )
	    if( pubkey_table[i].algo == algo )
		return pubkey_table[i].nskey;
    } while( load_pubkey_modules() );

#ifndef USE_RSA
    if( is_RSA(algo) )
	return 6;
#endif

    if(algo==PUBKEY_ALGO_ELGAMAL)
      return 4;

    return 0;
}
