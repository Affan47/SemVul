RNGSystemSeed(const rng rngx, void *p, unsigned long *pnSeed)
{

    int f = FALSE;
    rngcontext *rngctx = (rngcontext *) p;
    unsigned int n = 0;

#if HAVE_LIBGMP
#if !defined(WIN32)
    int h;
#endif
    if (!pnSeed) {
#if defined(WIN32)

        guint32 achState;
        mpz_t n;

        GTimeVal tv;
        g_get_current_time(&tv);
        achState = (unsigned int) tv.tv_sec ^ (unsigned int) tv.tv_usec;

        mpz_init(n);
        mpz_import(n, 1, -1, sizeof(guint32), 0, 0, &achState);
        InitRNGSeedMP(n, rngx, rngctx);
        mpz_clear(n);

        return TRUE;
#else


        if ((h = open("/dev/urandom", O_RDONLY)) >= 0) {
            char achState[64];

            if (read(h, achState, 64) == 64) {
                mpz_t n;

                close(h);

                mpz_init(n);
                mpz_import(n, 16, -1, 4, 0, 0, achState);
                InitRNGSeedMP(n, rngx, rngctx);
                mpz_clear(n);

                return TRUE;
            } else
                close(h);
        }
#endif

    }
#else
#if !defined(WIN32)
    int h;
    if ((h = open("/dev/urandom", O_RDONLY)) >= 0) {
        f = read(h, &n, sizeof n) == sizeof n;
        close(h);
    }
#endif

#endif

    if (!f) {
        GTimeVal tv;
        g_get_current_time(&tv);
        n = (unsigned int) tv.tv_sec ^ (unsigned int) tv.tv_usec;
    }

    InitRNGSeed(n, rngx, rngctx);
#if HAVE_LIBGMP
    mpz_set_ui(rngctx->nz, (unsigned long) n);
#endif

    if (pnSeed)
        *pnSeed = (unsigned long) n;

    return f;

}
