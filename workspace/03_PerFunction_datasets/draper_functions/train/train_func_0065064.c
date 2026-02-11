v_resample(uint8_t *dst, int dst_width, const uint8_t *src,
                       int wrap, int16_t *filter)
{
    int sum, i;
    const uint8_t *s;

    s = src;
    for(i=0;i<dst_width;i++) {
#if NB_TAPS == 4
        sum = s[0 * wrap] * filter[0] +
            s[1 * wrap] * filter[1] +
            s[2 * wrap] * filter[2] +
            s[3 * wrap] * filter[3];
#else
        {
            int j;
            uint8_t *s1 = s;

            sum = 0;
            for(j=0;j<NB_TAPS;j++) {
                sum += s1[0] * filter[j];
                s1 += wrap;
            }
        }
#endif
        sum = sum >> FILTER_BITS;
        if (sum < 0)
            sum = 0;
        else if (sum > 255)
            sum = 255;
        dst[0] = sum;
        dst++;
        s++;
    }
}
