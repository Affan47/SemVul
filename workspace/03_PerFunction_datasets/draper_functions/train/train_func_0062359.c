agentx_realloc_build_oid(u_char ** buf, size_t * buf_len, size_t * out_len,
                         int allow_realloc,
                         int inclusive, oid * name, size_t name_len,
                         int network_order)
{
    size_t          ilen = *out_len, i = 0;
    int             prefix = 0;

    DEBUGPRINTINDENT("dumpv_send");
    DEBUGMSG(("dumpv_send", "OID: "));
    DEBUGMSGOID(("dumpv_send", name, name_len));
    DEBUGMSG(("dumpv_send", "\n"));


    if (name_len == 0)
        inclusive = 0;


    if (name_len >= 5 && (name[0] == 1 && name[1] == 3 &&
                          name[2] == 6 && name[3] == 1 &&
                          name[4] > 0 && name[4] < 256)) {
        prefix = name[4];
        name += 5;
        name_len -= 5;
    }

    while ((*out_len + 4 + (4 * name_len)) >= *buf_len) {
        if (!(allow_realloc && snmp_realloc(buf, buf_len))) {
            return 0;
        }
    }

    *(*buf + *out_len) = (u_char) name_len;
    (*out_len)++;
    *(*buf + *out_len) = (u_char) prefix;
    (*out_len)++;
    *(*buf + *out_len) = (u_char) inclusive;
    (*out_len)++;
    *(*buf + *out_len) = (u_char) 0x00;
    (*out_len)++;

    DEBUGDUMPHEADER("send", "OID Header");
    DEBUGDUMPSETUP("send", (*buf + ilen), 4);
    DEBUGMSG(("dumpv_send", "  # subids:\t%d (0x%.2X)\n", (int)name_len,
              (unsigned int)name_len));
    DEBUGPRINTINDENT("dumpv_send");
    DEBUGMSG(("dumpv_send", "  prefix:\t%d (0x%.2X)\n", prefix, prefix));
    DEBUGPRINTINDENT("dumpv_send");
    DEBUGMSG(("dumpv_send", "  inclusive:\t%d (0x%.2X)\n", inclusive,
              inclusive));
    DEBUGINDENTLESS();
    DEBUGDUMPHEADER("send", "OID Segments");

    for (i = 0; i < name_len; i++) {
        if (!agentx_realloc_build_int(buf, buf_len, out_len, allow_realloc,
                                      name[i], network_order)) {
            DEBUGINDENTLESS();
            return 0;
        }
    }
    DEBUGINDENTLESS();

    return 1;
}
