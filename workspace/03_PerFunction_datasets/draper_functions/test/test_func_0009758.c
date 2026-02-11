mul2(const uint8 *in, uint8 *out)
{
	int i, t = in[0] >> 7;
    for(i = 0; i < 15; i++)
        out[i] = (in[i] << 1) | (in[i + 1] >> 7);
    out[15] = (in[15] << 1) ^ cst_mul[t];
}
