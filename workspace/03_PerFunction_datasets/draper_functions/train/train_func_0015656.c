apcm_quantization(int16_t xM[13],
                              int16_t xMc[13],
                              int16_t *mant_out,
                              int16_t *exp_out,
                              int16_t *xmaxc_out)
{

    static const int16_t gsm_NRFAC[8] =
    {
        29128, 26215, 23832, 21846, 20165, 18725, 17476, 16384
    };
    int i;
    int itest;
    int16_t xmax;
    int16_t xmaxc;
    int16_t temp;
    int16_t temp1;
    int16_t temp2;
    int16_t exp;
    int16_t mant;


    xmax = 0;
    for (i = 0;  i < 13;  i++)
    {
        temp = xM[i];
        temp = gsm_abs(temp);
        if (temp > xmax)
            xmax = temp;

    }


    exp = 0;
    temp = xmax >> 9;
    itest = 0;

    for (i = 0;  i <= 5;  i++)
    {
        itest |= (temp <= 0);
        temp >>= 1;

        assert(exp <= 5);
        if (itest == 0)
            exp++;

    }


    assert(exp <= 6  &&  exp >= 0);
    temp = (int16_t) (exp + 5);

    assert(temp <= 11  &&  temp >= 0);
    xmaxc = gsm_add((xmax >> temp), exp << 3);


    apcm_quantization_xmaxc_to_exp_mant(xmaxc, &exp, &mant);


    assert(exp <= 4096  &&  exp >= -4096);
    assert(mant >= 0  &&  mant <= 7);

    temp1 = (int16_t) (6 - exp);
    temp2 = gsm_NRFAC[mant];

    for (i = 0;  i < 13;  i++)
    {
        assert(temp1 >= 0  &&  temp1 < 16);

        temp = xM[i] << temp1;
        temp = gsm_mult(temp, temp2);
        temp >>= 12;
        xMc[i] = (int16_t) (temp + 4);
    }


    *mant_out  = mant;
    *exp_out   = exp;
    *xmaxc_out = xmaxc;
}
