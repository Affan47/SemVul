dsa_generate(int size)
{
    DSA *dsa;
    unsigned char seed[20];
    int seed_len = 20, counter;
    unsigned long h;

    if (!RAND_bytes(seed, seed_len)) {
	return 0;
    }
    dsa = DSA_generate_parameters(size, seed, seed_len, &counter, &h,
	    rb_block_given_p() ? ossl_generate_cb : NULL,
	    NULL);
    if(!dsa) return 0;

    if (!DSA_generate_key(dsa)) {
	DSA_free(dsa);
	return 0;
    }

    return dsa;
}
