cf_put_long_run(stream_CFE_state * ss, byte * q, int lenv, const cf_runs * prt)
{
    hce_declare_state;
    cfe_run rr;

#if defined(DEBUG) && !defined(GS_THREADSAFE)
    stats_runs_t *pstats =
    (prt == &cf_white_runs ? &stats_white_runs : &stats_black_runs);

#endif

    hce_load_state();
    while (lenv >= 2560 + 64) {
        rr = prt->make_up[40];
        COUNT_RUN(pstats->make_up, 40);
        hc_put_value(ss, q, rr.code, rr.code_length);
        lenv -= 2560;
    }
    rr = prt->make_up[lenv >> 6];
    COUNT_RUN(pstats->make_up, lenv >> 6);
    hc_put_value(ss, q, rr.code, rr.code_length);
    hce_store_state();
    return q;
}
