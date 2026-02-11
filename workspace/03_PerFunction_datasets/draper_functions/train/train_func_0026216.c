strong_rng(csprng *rng)
{
    int r;
    r=rng->pool[rng->pool_ptr++];
    if (rng->pool_ptr>=MR_HASH_BYTES) fill_pool(rng);
    return r;
}
