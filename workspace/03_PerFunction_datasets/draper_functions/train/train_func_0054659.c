periodogram_generate_coeffs(complexf_t coeffs[], float freq, int sample_rate, int window_len)
{
    float window;
    float sum;
    float x;
    int i;

    sum = 0.0f;
    for (i = 0;  i < window_len/2;  i++)
    {

        window = 0.53836f - 0.46164f*cosf(2.0f*3.1415926535f*i/(window_len - 1.0f));
        x = (i - window_len/2.0f + 0.5f)*freq*2.0f*3.1415926535f/sample_rate;
        coeffs[i].re = cosf(x)*window;
        coeffs[i].im = -sinf(x)*window;
        sum += window;
    }


    sum = 1.0f/(2.0f*sum);
    for (i = 0;  i < window_len/2;  i++)
    {
        coeffs[i].re *= sum;
        coeffs[i].im *= sum;
    }
    return window_len/2;
}
