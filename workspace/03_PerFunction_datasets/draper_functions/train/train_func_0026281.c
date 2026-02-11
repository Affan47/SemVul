readbyte(__G)
    __GDEF
{
    if (G.mem_mode)
        return EOF;
    if (G.csize <= 0) {
        G.csize--;
        G.incnt = 0;
        return EOF;
    }
    if (G.incnt <= 0) {
        if ((G.incnt = read(G.zipfd, (char *)G.inbuf, INBUFSIZ)) == 0) {
            return EOF;
        } else if (G.incnt < 0) {

            (*G.message)((zvoid *)&G,
              (uch *)LoadFarString(ReadError),
              (ulg)strlen(LoadFarString(ReadError)), 0x401);
            echon();
#ifdef WINDLL
            longjmp(dll_error_return, 1);
#else
            DESTROYGLOBALS();
            EXIT(PK_BADERR);
#endif
        }
        G.cur_zipfile_bufstart += INBUFSIZ;
        G.inptr = G.inbuf;
        defer_leftover_input(__G);
    }

#if CRYPT
    if (G.pInfo->encrypted) {
        uch *p;
        int n;


        for (n = G.incnt, p = G.inptr;  n--;  p++)
            zdecode(*p);
    }
#endif

    --G.incnt;
    return *G.inptr++;

}
