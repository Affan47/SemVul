set_output_file(const char *fname)
{
    int     retvalue = FAIL;
    FILE    *f;


    if (rawoutstream && rawoutstream != stdout) {
        if (HDfclose(rawoutstream))
            HDperror("closing rawoutstream");
        else
            rawoutstream = NULL;
    }

    if (fname != NULL) {
        if ((f = HDfopen(fname, "w")) != NULL) {
                rawoutstream = f;
                retvalue = SUCCEED;
        }
    }
    else {
        rawoutstream = NULL;
        retvalue = SUCCEED;
    }

    return retvalue;
}
