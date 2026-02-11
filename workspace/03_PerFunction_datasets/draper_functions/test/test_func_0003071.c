_increment_counter(uint8_t* in, size_t len)
{
    int i;

    if (len <= 0)
    {
        meh_warn("negative length passed to _increment_counter in pbkdf2");
        return;
    }

    for (i = len-1; i >= 0; i--)
        if (++in[i])
            break;
}
