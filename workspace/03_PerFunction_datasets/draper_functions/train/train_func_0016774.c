increment_abs(char *ext)
{
    size_t idx;
    int exp = get_exp(ext);
    int carry;


    idx = (exp <= 0 ? 0 : (size_t)exp);


    if (idx > get_prec(ext))
        return;


    for (carry = TRUE ; idx != 0 ; )
    {
        int dig;


        --idx;


        dig = get_dig(ext, idx);


        if (dig == 9)
        {

            set_dig(ext, idx, 0);
        }
        else
        {

            set_dig(ext, idx, dig + 1);


            carry = FALSE;


            break;
        }
    }


    if (carry)
    {


        while (get_exp(ext) < 0)
        {

            shift_right(ext, 1);
            set_exp(ext, get_exp(ext) + 1);
        }


        shift_right(ext, 1);
        set_exp(ext, get_exp(ext) + 1);


        set_dig(ext, 0, 1);
    }


    ext[VMBN_FLAGS] &= ~VMBN_F_ZERO;
}
