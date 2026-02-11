read_float4_array(int f, float *x, int n)
{
#ifdef _CRAY

    long *buffer;
    int i, nread;

    buffer = (long *)G_malloc((n + 1) * 4);
    if (!buffer)
	return 0;
    nread = read(f, buffer, n * 4);
    if (nread <= 0)
	return 0;
    nread /= 4;
    ieee_to_cray_array(x, buffer, nread);
    G_free(buffer);
    return nread;
#else
    int nread = read(f, x, 4 * n);

    if (nread <= 0)
	return 0;
#ifdef LITTLE
    flip4((const unsigned int *)x, (unsigned int *)x, nread / 4);
#endif
    return nread / 4;
#endif
}
