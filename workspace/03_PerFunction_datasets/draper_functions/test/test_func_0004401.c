shift_left(char *ext, unsigned int shift)
{
    size_t prec = get_prec(ext);
    size_t i;


    if (shift == 0)
        return;


    if ((shift & 1) == 0)
    {

        for (i = 0 ; i + shift/2 < (prec+1)/2 ; ++i)
            ext[VMBN_MANT + i] = ext[VMBN_MANT + i + shift/2];


        for ( ; i < (prec+1)/2 ; ++i)
            ext[VMBN_MANT + i] = 0;


        set_dig(ext, prec - shift, 0);
    }
    else
    {

        for (i = 0 ; i + shift < prec  ; ++i)
        {
            unsigned int dig;


            dig = get_dig(ext, i + shift);


            set_dig(ext, i, dig);
        }


        for ( ; i < prec ; ++i)
            set_dig(ext, i, 0);
    }
}
