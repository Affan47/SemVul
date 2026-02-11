count_bit_noESC(const int *ix, const int *end, int mx, unsigned int *s)
{

    unsigned int sum1 = 0;
    const uint8_t *const hlen1 = ht[1].hlen;
    (void) mx;

    do {
        unsigned int const x0 = *ix++;
        unsigned int const x1 = *ix++;
        sum1 += hlen1[ x0+x0 + x1 ];
    } while (ix < end);

    *s += sum1;
    return 1;
}
