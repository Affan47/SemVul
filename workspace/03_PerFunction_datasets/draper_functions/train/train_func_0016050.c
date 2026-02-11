agentx_parse_int(u_char * data, u_int network_byte_order)
{
    u_int           value = 0;


    DEBUGDUMPSETUP("recv", data, 4);
    if (network_byte_order) {
        memmove(&value, data, 4);
#ifndef WORDS_BIGENDIAN
        value = ntohl(value);
#endif
    } else {
#ifndef WORDS_BIGENDIAN
        memmove(&value, data, 4);
#else


        value += data[3];
        value <<= 8;
        value += data[2];
        value <<= 8;
        value += data[1];
        value <<= 8;
        value += data[0];
#endif
    }
    DEBUGMSG(("dumpv_recv", "  Integer:\t%u (0x%.2X)\n", value, value));

    return value;
}
