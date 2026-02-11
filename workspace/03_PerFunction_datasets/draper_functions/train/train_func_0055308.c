fffi8i8(LONGLONG *input,
            long ntodo,
            double scale,
            double zero,
            int nullcheck,


            LONGLONG tnull,
            LONGLONG nullval,
            char *nullarray,
            int  *anynull,
            LONGLONG *output,
            int *status)


{
    long ii;
    double dvalue;

    if (nullcheck == 0)
    {
        if (scale == 1. && zero == 0.)
        {
            for (ii = 0; ii < ntodo; ii++)
                output[ii] =  input[ii];
        }
        else
        {
            for (ii = 0; ii < ntodo; ii++)
            {
                dvalue = input[ii] * scale + zero;

                if (dvalue < DLONGLONG_MIN)
                {
                    *status = OVERFLOW_ERR;
                    output[ii] = LONGLONG_MIN;
                }
                else if (dvalue > DLONGLONG_MAX)
                {
                    *status = OVERFLOW_ERR;
                    output[ii] = LONGLONG_MAX;
                }
                else
                    output[ii] = (LONGLONG) dvalue;
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

                    if (dvalue < DLONGLONG_MIN)
                    {
                        *status = OVERFLOW_ERR;
                        output[ii] = LONGLONG_MIN;
                    }
                    else if (dvalue > DLONGLONG_MAX)
                    {
                        *status = OVERFLOW_ERR;
                        output[ii] = LONGLONG_MAX;
                    }
                    else
                        output[ii] = (LONGLONG) dvalue;
                }
            }
        }
    }
    return(*status);
}
