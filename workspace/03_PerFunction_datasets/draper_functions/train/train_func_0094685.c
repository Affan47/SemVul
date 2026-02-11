fffi2i2(short *input,
            long ntodo,
            double scale,
            double zero,
            int nullcheck,


            short tnull,
            short nullval,
            char *nullarray,
            int  *anynull,
            short *output,
            int *status)


{
    long ii;
    double dvalue;

    if (nullcheck == 0)
    {
        if (scale == 1. && zero == 0.)
        {
            memcpy(output, input, ntodo * sizeof(short) );
        }
        else
        {
            for (ii = 0; ii < ntodo; ii++)
            {
                dvalue = input[ii] * scale + zero;

                if (dvalue < DSHRT_MIN)
                {
                    *status = OVERFLOW_ERR;
                    output[ii] = SHRT_MIN;
                }
                else if (dvalue > DSHRT_MAX)
                {
                    *status = OVERFLOW_ERR;
                    output[ii] = SHRT_MAX;
                }
                else
                    output[ii] = (short) dvalue;
            }
        }
    }
    else
    {
        if (scale == 1. && zero == 0.)
        {
            for (ii = 0; ii < ntodo; ii++)
            {
                if (input[ii] == tnull)
                {
                    *anynull = 1;
                    if (nullcheck == 1)
                        output[ii] = nullval;
                    else
                        nullarray[ii] = 1;
                }
                else
                    output[ii] = input[ii];
            }
        }
        else
        {
            for (ii = 0; ii < ntodo; ii++)
            {
                if (input[ii] == tnull)
                {
                    *anynull = 1;
                    if (nullcheck == 1)
                        output[ii] = nullval;
                    else
                        nullarray[ii] = 1;
                }
                else
                {
                    dvalue = input[ii] * scale + zero;

                    if (dvalue < DSHRT_MIN)
                    {
                        *status = OVERFLOW_ERR;
                        output[ii] = SHRT_MIN;
                    }
                    else if (dvalue > DSHRT_MAX)
                    {
                        *status = OVERFLOW_ERR;
                        output[ii] = SHRT_MAX;
                    }
                    else
                        output[ii] = (short) dvalue;
                }
            }
        }
    }
    return(*status);
}
