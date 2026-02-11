fflongfi8(long *input,
            long ntodo,
            double scale,
            double zero,
            LONGLONG *output,
            int *status)


{
    long ii;
    double dvalue;

    if (scale == 1. && zero == 0.)
    {
        for (ii = 0; ii < ntodo; ii++)
                output[ii] = input[ii];
    }
    else
    {
        for (ii = 0; ii < ntodo; ii++)
        {
            dvalue = (input[ii] - zero) / scale;

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
            {
                if (dvalue >= 0)
                    output[ii] = (LONGLONG) (dvalue + .5);
                else
                    output[ii] = (LONGLONG) (dvalue - .5);
            }
        }
    }
    return(*status);
}
