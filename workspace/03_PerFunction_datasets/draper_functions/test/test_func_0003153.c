ffi2fr8(short *input,
            long ntodo,
            double scale,
            double zero,
            double *output,
            int *status)


{
    long ii;

    if (scale == 1. && zero == 0.)
    {
        for (ii = 0; ii < ntodo; ii++)
                output[ii] = (double) input[ii];
    }
    else
    {
        for (ii = 0; ii < ntodo; ii++)
            output[ii] = (input[ii] - zero) / scale;
    }
    return(*status);
}
