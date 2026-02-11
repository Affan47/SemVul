ffr4fi1(float *input,
            long ntodo,
            double scale,
            double zero,
            unsigned char *output,
            int *status)


{
    long ii;
    double dvalue;

    if (scale == 1. && zero == 0.)
    {
        for (ii = 0; ii < ntodo; ii++)
        {
            if (input[ii] < DUCHAR_MIN)
            {
                *status = OVERFLOW_ERR;
                output[ii] = 0;
            }
            else if (input[ii] > DUCHAR_MAX)
            {
                *status = OVERFLOW_ERR;
                output[ii] = UCHAR_MAX;
            }
            else
                output[ii] = (unsigned char) input[ii];
        }
    }
    else
    {
        for (ii = 0; ii < ntodo; ii++)
        {
            dvalue = (input[ii] - zero) / scale;

            if (dvalue < DUCHAR_MIN)
            {
                *status = OVERFLOW_ERR;
                output[ii] = 0;
            }
            else if (dvalue > DUCHAR_MAX)
            {
                *status = OVERFLOW_ERR;
                output[ii] = UCHAR_MAX;
            }
            else
                output[ii] = (unsigned char) (dvalue + .5);
        }
    }
    return(*status);
}
