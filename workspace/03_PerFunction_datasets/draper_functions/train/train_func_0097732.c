hmac_sha_data(const unsigned char data[], unsigned long data_len, hmac_ctx cx[1])
{   unsigned int i;

    if(cx->klen != HMAC_IN_DATA)
    {
        if(cx->klen > HASH_INPUT_SIZE)
        {
            sha_end(cx->key, cx->ctx);
            cx->klen = HASH_OUTPUT_SIZE;
        }


        memset(cx->key + cx->klen, 0, HASH_INPUT_SIZE - cx->klen);


        for(i = 0; i < (HASH_INPUT_SIZE >> 2); ++i)
            ((unsigned long*)cx->key)[i] ^= 0x36363636;


        sha_begin(cx->ctx);
        sha_hash(cx->key, HASH_INPUT_SIZE, cx->ctx);


        cx->klen = HMAC_IN_DATA;
    }


    if(data_len)
        sha_hash(data, data_len, cx->ctx);
}
