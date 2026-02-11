list_add_safe (listz_t ret, listz_t a, listz_t b,
                        unsigned int sizea, unsigned int sizeb,
                        unsigned int needed)
{
    unsigned int i;
    unsigned int safe;
    safe = MIN(sizea, sizeb);
    safe = MIN(safe, needed);

    list_add (ret, a, b, i = safe);

    while (i < needed)
    {
        if (i < sizea)
        {
            if (i < sizeb)
                mpz_add (ret[i], a[i], b[i]);
            else
                mpz_set (ret[i], a[i]);
        }
        else
        {
            if (i < sizeb)
                mpz_set (ret[i], b[i]);
            else
                mpz_set_ui (ret[i], 0);
        }
        i++;
    }
}
