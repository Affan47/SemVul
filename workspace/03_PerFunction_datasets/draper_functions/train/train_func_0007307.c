periodogram_prepare(complexf_t sum[], complexf_t diff[], const complexf_t amp[], int len)
{
    int i;

    for (i = 0;  i < len/2;  i++)
    {
        sum[i] = complex_addf(&amp[i], &amp[len - 1 - i]);
        diff[i] = complex_subf(&amp[i], &amp[len - 1 - i]);
    }
    return len/2;
}
