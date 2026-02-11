ajCharNewResC(const char* txt, size_t size)
{
    static char* cp;
    size_t isize;
    size_t ilen;

    isize = size;

    if(txt)
    {
        ilen = strlen(txt);

        if(ilen >= isize)
            isize = ilen + 1;

        cp = (char*) AJALLOC0(isize);
        memmove(cp, txt, ilen+1);
    }
    else
    {
        cp = (char*) AJALLOC0(isize);
    }

    return cp;
}
