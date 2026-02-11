mix2to1 (sample_t * dest, sample_t * src, sample_t bias)
{
    int i;

    for (i = 0; i < 256; i++)
	dest[i] += BIAS (src[i]);
}
