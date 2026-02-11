rsa_generate( int algo, unsigned nbits, MPI *skey, MPI **retfactors )
{
    RSA_secret_key sk;

    if( !is_RSA(algo) )
	return G10ERR_PUBKEY_ALGO;

    generate( &sk, nbits );
    skey[0] = sk.n;
    skey[1] = sk.e;
    skey[2] = sk.d;
    skey[3] = sk.p;
    skey[4] = sk.q;
    skey[5] = sk.u;

    if (retfactors)
      *retfactors = xmalloc_clear( 1 * sizeof **retfactors );
    return 0;
}
