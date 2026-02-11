generate_all_key2_bits_31_2(uint32_t *key2, const uint16_t *key2_bits_15_2)
{
    uint32_t i, j;
    for (i = 0; i < pow2(16); ++i)
        for (j = 0; j < 64; ++j)
            key2[i * 64 + j] = (i << 16) | key2_bits_15_2[j];
}
