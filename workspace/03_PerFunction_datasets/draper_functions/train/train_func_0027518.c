is_frac_zero(const char *ext)
{
    size_t idx;
    int exp = get_exp(ext);
    size_t prec = get_prec(ext);


    idx = (exp <= 0 ? 0 : (size_t)exp);


    for ( ; idx < prec ; ++idx)
    {

        if (get_dig(ext, idx) != 0)
            return FALSE;
    }


    return TRUE;
}
