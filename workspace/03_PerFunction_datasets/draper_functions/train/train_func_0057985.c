meh_update_salsa20(MehSalsa20 s20, const unsigned char* in,
                               unsigned char* out, size_t len, size_t* got)
{
    uint32_t i;
    uint32_t index;
    uint32_t* state;
    uint8_t* keystream;

    if (NULL == in || NULL == got ||  NULL == out || NULL == s20)
        return meh_error("null reference passed to meh_update_salsa20",
                         MEH_INVALID_ARGUMENT);

    state = s20->state;
    keystream = s20->keystream;

    index = s20->index;
    for (i = 0; i < len; i++, index++)
    {
        if (64 == index)
        {
            meh_salsa20_core(keystream, state);
            index = 0;
        }

        out[i] = in[i] ^ keystream[index];
    }

    s20->index = index;

    *got = len;

    return MEH_OK;
}
