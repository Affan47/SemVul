do_prim(fp, tag, enc, len, lev)
    FILE *fp;
    int tag;
    unsigned char *enc;
    int len;
    int lev;
{
    int n;
    int i;
    int j;
    int width;

    if (do_prim_string(fp, tag, enc, len, lev))
        return OK;
    if (do_prim_int(fp, tag, enc, len, lev))
        return OK;
    if (do_prim_bitstring(fp, tag, enc, len, lev))
        return OK;

    if (print_primitive_length)
        fprintf(fp, " <%d>", len);

    width = (80 - (lev * 3) - 8) / 4;

    for (n = 0; n < len; n++) {
        if ((n % width) == 0) {
            fprintf(fp, "\n");
            for (i=0; i<lev; i++) fprintf(fp, "   ");
        }
        fprintf(fp, "%02x ", enc[n]);
        if ((n % width) == (width-1)) {
            fprintf(fp, "    ");
            for (i=n-(width-1); i<=n; i++)
                if (isprint(enc[i])) fprintf(fp, "%c", enc[i]);
                else fprintf(fp, ".");
        }
    }
    if ((j = (n % width)) != 0) {
        fprintf(fp, "    ");
        for (i=0; i<width-j; i++) fprintf(fp, "   ");
        for (i=n-j; i<n; i++)
            if (isprint(enc[i])) fprintf(fp, "%c", enc[i]);
            else fprintf(fp, ".");
    }
    return(OK);
}
