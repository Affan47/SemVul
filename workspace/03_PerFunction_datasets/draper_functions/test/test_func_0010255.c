dm_round (int rounds, uint32_t *array, uint32_t *h0, uint32_t *h1)
{
        uint32_t sum = 0;
        int      n = 0;
        uint32_t b0  = 0;
        uint32_t b1  = 0;

        b0 = *h0;
        b1 = *h1;

        n = rounds;

        do {
                sum += DM_DELTA;
                b0  += ((b1 << 4) + array[0])
                        ^ (b1 + sum)
                        ^ ((b1 >> 5) + array[1]);
                b1  += ((b0 << 4) + array[2])
                        ^ (b0 + sum)
                        ^ ((b0 >> 5) + array[3]);
        } while (--n);

        *h0 += b0;
        *h1 += b1;

        return 0;
}
