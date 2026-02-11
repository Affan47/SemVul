nsslow_GetFIPSEnabled(void) {
#ifdef LINUX
    FILE *f;
    char d;
    size_t size;

    f = fopen("/proc/sys/crypto/fips_enabled", "r");
    if (!f)
        return 0;

    size = fread(&d, 1, 1, f);
    fclose(f);
    if (size != 1)
        return 0;
    if (d != '1')
        return 0;
#endif
    return 1;
}
