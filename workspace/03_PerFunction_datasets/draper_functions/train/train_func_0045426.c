fffi1r4(unsigned char *input,
            long ntodo,
            double scale,
            double zero,
            int nullcheck,


            unsigned char tnull,
            float nullval,
            char *nullarray,
            int  *anynull,
            float *output,
            int *status)


{
    long ii;

    if (nullcheck == 0)
    {
        if (scale == 1. && zero == 0.)
        {
            for (ii = 0; ii < ntodo; ii++)
                output[ii] = (float) input[ii];
        }
        else
        {
            for (ii = 0; ii < ntodo; ii++)
            {
                output[ii] = (float) (( (double) input[ii] ) * scale + zero);
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
                    output[ii] = (float) input[ii];
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
                    output[ii] = (float) (( (double) input[ii] ) * scale + zero);
                }
            }
        }
    }
    return(*status);
}
