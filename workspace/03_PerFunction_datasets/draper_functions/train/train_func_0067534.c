parseQuoteString(FILE * fp, char *token, int maxtlen)
{
    register int    ch;
    int             count = 0;
    int             too_long = 0;
    char           *token_start = token;

    for (ch = getc(fp); ch != EOF; ch = getc(fp)) {
        if (ch == '\r')
            continue;
        if (ch == '\n') {
            mibLine++;
        } else if (ch == '"') {
            *token = '\0';
            if (too_long && netsnmp_ds_get_int(NETSNMP_DS_LIBRARY_ID,
					   NETSNMP_DS_LIB_MIB_WARNINGS) > 1) {


                char            ch_save = *(token_start + 50);
                *(token_start + 50) = '\0';
                print_error("Warning: string too long",
                            token_start, QUOTESTRING);
                *(token_start + 50) = ch_save;
            }
            return QUOTESTRING;
        }


        if (++count < maxtlen)
            *token++ = ch;
        else
            too_long = 1;
    }

    return 0;
}
