datafile_is_block_zero(cdatafile *f, char *data, u64 len)
{
    bool zero=true;
    u64 pos;

    for (pos=0; (pos<len) && (zero==true); pos++)
        if (data[pos]!=0)
            zero=false;

    return zero;
}
