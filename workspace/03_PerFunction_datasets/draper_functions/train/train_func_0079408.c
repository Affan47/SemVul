rng_nix(unsigned char *buf, unsigned long len,
                             void (*callback)(void))
{
#ifdef LTC_NO_FILE
    return 0;
#else
    FILE *f;
    unsigned long x;
#ifdef TRY_URANDOM_FIRST
    f = fopen("/dev/urandom", "rb");
    if (f == NULL)
#endif
       f = fopen("/dev/random", "rb");

    if (f == NULL) {
       return 0;
    }


    if (setvbuf(f, NULL, _IONBF, 0) != 0) {
       fclose(f);
       return 0;
    }

    x = (unsigned long)fread(buf, 1, (size_t)len, f);
    fclose(f);
    return x;
#endif
}
