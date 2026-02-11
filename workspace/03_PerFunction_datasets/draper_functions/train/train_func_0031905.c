strong_init(csprng *rng,int rawlen,char *raw,mr_unsign32 tod)
{

    int i;
    mr_unsign32 hash[MR_HASH_BYTES/4];
    sha256 sh;
    rng->pool_ptr=0;
    for (i=0;i<NK;i++) rng->ira[i]=0;
    if (rawlen>0)
    {
        shs256_init(&sh);
        for (i=0;i<rawlen;i++)
            shs256_process(&sh,raw[i]);
        shs256_hash(&sh,(char *)hash);


        for (i=0;i<MR_HASH_BYTES/4;i++) sirand(rng,hash[i]);
    }
    sirand(rng,tod);

    fill_pool(rng);
}
