fclose_and_check(FILE *fp, const char *fn)
{
    if (fclose(fp))
    {
        fatal_intl_close(fn);

    }
}
