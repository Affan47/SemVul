ff_celp_convolve_circ(
        int16_t* fc_out,
        const int16_t* fc_in,
        const int16_t* filter,
        int len)
{
    int i, k;

    memset(fc_out, 0, len * sizeof(int16_t));


    for(i=0; i<len; i++)
    {
        if(fc_in[i])
        {
            for(k=0; k<i; k++)
                fc_out[k] += (fc_in[i] * filter[len + k - i]) >> 15;

            for(k=i; k<len; k++)
                fc_out[k] += (fc_in[i] * filter[      k - i]) >> 15;
        }
    }
}
