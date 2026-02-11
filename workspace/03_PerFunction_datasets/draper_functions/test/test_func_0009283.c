map(wchar_t unicode_char,
                                       char **output_ptr,
                                       size_t *output_len) const
{

    if (*output_len < sizeof(wchar_t))
    {
        *output_len = 0;
        return sizeof(wchar_t);
    }


    **(wchar_t **)output_ptr = unicode_char;


    ++(*(wchar_t **)output_ptr);


    return sizeof(wchar_t);
}
