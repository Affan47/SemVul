voc_push_strlist(voccxdef *ctx, char *firstwrd, char *lastwrd)
{
    size_t curlen;
    char *p;
    uint lstsiz;
    uchar *lstp;


    for (lstsiz = 0, p = firstwrd ; p != 0 && p <= lastwrd ; p += curlen + 1)
    {
        curlen = strlen(p);
        lstsiz += curlen + (1+2);
    }


    lstp = voc_push_list_siz(ctx, lstsiz);


    for (p = firstwrd ; p != 0 && p <= lastwrd ; p += curlen + 1)
    {

        *lstp++ = DAT_SSTRING;


        curlen = strlen(p);
        oswp2(lstp, curlen + 2);
        lstp += 2;


        memcpy(lstp, p, curlen);
        lstp += curlen;
    }
}
