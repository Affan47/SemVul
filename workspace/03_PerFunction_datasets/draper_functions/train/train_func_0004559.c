fn_gets_8(const gs_function_Sd_t * pfn, ulong offset, uint * samples)
{
    SETUP_SAMPLES(8, n);
    for (i = 0; i < n; ++i) {
        samples[i] = *p++;
    }
    return 0;
}
