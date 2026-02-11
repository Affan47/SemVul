str_catenate(string_ty *s1, string_ty *s2)
{
    static char     *tmp;
    static size_t   tmplen;
    string_ty       *s;
    size_t          length;

    length = s1->str_length + s2->str_length;
    if (tmplen < length)
    {
        tmplen = length;
        tmp = mem_change_size(tmp, tmplen);
    }
    memcpy(tmp, s1->str_text, s1->str_length);
    memcpy(tmp + s1->str_length, s2->str_text, s2->str_length);
    s = str_n_from_c(tmp, length);
    return s;
}
