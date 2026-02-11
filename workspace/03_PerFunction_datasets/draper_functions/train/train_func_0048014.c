ffi2fr4(short *input,
            long ntodo,
            double scale,
            double zero,
            float *output,
            int *status)


{
    long ii;

    if (scale == 1. && zero == 0.)
    {
        for (ii = 0; ii < ntodo; ii++)
                output[ii] = (float) input[ii];
    }
    else
    {
        for (ii = 0; ii < ntodo; ii++)
            output[ii] = (float) ((input[ii] - zero) / scale);
    }
    return(*status);
}
