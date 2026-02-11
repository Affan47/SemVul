asn_realloc_rbuild_string(u_char ** pkt, size_t * pkt_len,
                          size_t * offset, int r,
                          u_char type,
                          const u_char * str, size_t strlength)
{
    static const char *errpre = "build string";
    size_t          start_offset = *offset;

    while ((*pkt_len - *offset) < strlength) {
        if (!(r && asn_realloc(pkt, pkt_len))) {
            return 0;
        }
    }

    *offset += strlength;
    memcpy(*pkt + *pkt_len - *offset, str, strlength);

    if (asn_realloc_rbuild_header
        (pkt, pkt_len, offset, r, type, strlength)) {
        if (_asn_realloc_build_header_check
            (errpre, pkt, pkt_len, strlength)) {
            return 0;
        } else {
            DEBUGDUMPSETUP("send", (*pkt + *pkt_len - *offset),
                           *offset - start_offset);
            DEBUGIF("dumpv_send") {
                if (strlength == 0) {
                    DEBUGMSG(("dumpv_send", "  String: [NULL]\n"));
                } else {
                    u_char         *buf = (u_char *) malloc(2 * strlength);
                    size_t          l =
                        (buf != NULL) ? (2 * strlength) : 0, ol = 0;

                    if (sprint_realloc_asciistring
                        (&buf, &l, &ol, 1, str, strlength)) {
                        DEBUGMSG(("dumpv_send", "  String:\t%s\n", buf));
                    } else {
                        if (buf == NULL) {
                            DEBUGMSG(("dumpv_send",
                                      "  String:\t[TRUNCATED]\n"));
                        } else {
                            DEBUGMSG(("dumpv_send",
                                      "  String:\t%s [TRUNCATED]\n", buf));
                        }
                    }
                    if (buf != NULL) {
                        free(buf);
                    }
                }
            }
        }
        return 1;
    }

    return 0;
}
