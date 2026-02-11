dump_chunk(const char *debugtoken, const char *title, const u_char * buf,
           int size)
{
    int             printunit = 64;
    char            chunk[SNMP_MAXBUF], *s, *sp;

    if (title && (*title != '\0')) {
        DEBUGMSGTL((debugtoken, "%s\n", title));
    }


    memset(chunk, 0, SNMP_MAXBUF);
    size = binary_to_hex(buf, size, &s);
    sp = s;

    while (size > 0) {
        if (size > printunit) {
            memcpy(chunk, sp, printunit);
            chunk[printunit] = '\0';
            DEBUGMSGTL((debugtoken, "\t%s\n", chunk));
        } else {
            DEBUGMSGTL((debugtoken, "\t%s\n", sp));
        }

        sp += printunit;
        size -= printunit;
    }


    SNMP_FREE(s);

}
