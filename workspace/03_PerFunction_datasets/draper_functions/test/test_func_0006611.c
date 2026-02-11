meh_get_salsa20(const unsigned char* key,
			   const unsigned char* iv,
			   size_t key_size)
{
    MehSalsa20 r = malloc(sizeof (meh_salsa20_state_t));

    if (NULL == r)
    {
        meh_warn("could not allocate cipher context in meh_get_salsa20");
        return NULL;
    }

    meh_reset_salsa20(r, key, iv, key_size);

    return r;
}
