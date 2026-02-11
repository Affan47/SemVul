apcm_quantization_xmaxc_to_exp_mant(int16_t xmaxc,
                                                int16_t *exp_out,
                                                int16_t *mant_out)
{
    int16_t exp;
    int16_t mant;


    exp = 0;
    if (xmaxc > 15)
        exp = (int16_t) ((xmaxc >> 3) - 1);

    mant = xmaxc - (exp << 3);

    if (mant == 0)
    {
        exp = -4;
        mant = 7;
    }
    else
    {
        while (mant <= 7)
        {
            mant = (int16_t) (mant << 1 | 1);
            exp--;
        }

        mant -= 8;
    }


    assert(exp >= -4  &&  exp <= 6);
    assert(mant >= 0  &&  mant <= 7);

    *exp_out  = exp;
    *mant_out = mant;
}
