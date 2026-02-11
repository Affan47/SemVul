cpu_compliment(PLPA_NAME(cpu_set_t) *out, PLPA_NAME(cpu_set_t) *in)
{
    int i;
    PLPA_CPU_ZERO(out);
    for (i = 0; i < PLPA_BITMASK_CPU_MAX; ++i) {
        if (!PLPA_CPU_ISSET(i, in)) {
            PLPA_CPU_SET(i, out);
        }
    }
}
