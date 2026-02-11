find_substr(VMG_ const char *str, int start_idx,
                                      const char *substr, size_t *idxp)
{
    utf8_ptr p;
    size_t rem;
    size_t sublen;
    size_t char_ofs;
    int i;


    rem = vmb_get_len(str);
    sublen = vmb_get_len(substr);


    p.set((char *)str + 2);


    for (i = start_idx ; i > 0 && rem >= sublen ; --i, p.inc(&rem)) ;


    for (char_ofs = 0 ; rem != 0 && rem >= sublen ; ++char_ofs, p.inc(&rem))
    {

        if (memcmp(p.getptr(), substr + VMB_LEN, sublen) == 0)
        {

            if (idxp != 0)
                *idxp = char_ofs + start_idx;


            return p.getptr();
        }
    }


    return 0;
}
