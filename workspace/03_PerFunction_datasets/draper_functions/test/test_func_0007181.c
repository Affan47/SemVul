csngen_test ()
{
    int rc;
    CSNGen *gen = csngen_new (255, NULL);

    slapi_log_error(SLAPI_LOG_FATAL, NULL, "staring csn generator test ...");
    csngen_dump_state (gen);

    rc = _csngen_start_test_threads(gen);
    if (rc == 0)
    {
        DS_Sleep(PR_SecondsToInterval(TEST_TIME));
    }

    _csngen_stop_test_threads(gen);
    csngen_dump_state (gen);
    slapi_log_error(SLAPI_LOG_FATAL, NULL, "csn generator test is complete...");
}
