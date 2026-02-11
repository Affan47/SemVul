k5_prng_init(void)
{
    krb5_error_code ret = 0;
    unsigned char osbuf[64];

    ret = k5_mutex_finish_init(&fortuna_lock);
    if (ret)
        return ret;

    init_state(&main_state);
#ifdef _WIN32
    last_pid = GetCurrentProcessId();
#else
    last_pid = getpid();
#endif
    if (k5_get_os_entropy(osbuf, sizeof(osbuf))) {
        generator_reseed(&main_state, osbuf, sizeof(osbuf));
        have_entropy = TRUE;
    }

    return 0;
}
