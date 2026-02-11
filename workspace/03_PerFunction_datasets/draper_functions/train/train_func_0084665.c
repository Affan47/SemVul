ffintfi4(int *input,
            long ntodo,
            double scale,
            double zero,
            INT32BIT *output,
            int *status)


{
    long ii;
    double dvalue;

    if (scale == 1. && zero == 0.)
    {
        memcpy(output, input, ntodo * sizeof(int) );
    }
    else
    {
        for (ii = 0; ii < ntodo; ii++)
        {
            dvalue = (input[ii] - zero) / scale;

            if (dvalue < DINT_MIN)
            {
                *status = OVERFLOW_ERR;
                output[ii] = INT32_MIN;
            }
            else if (dvalue > DINT_MAX)
            {
                *status = OVERFLOW_ERR;
                output[ii] = INT32_MAX;
            }
            else
            {
                if (dvalue >= 0)
                    output[ii] = (INT32BIT) (dvalue + .5);
                else
                    output[ii] = (INT32BIT) (dvalue - .5);
            }
        }
    }
    return(*status);
}
