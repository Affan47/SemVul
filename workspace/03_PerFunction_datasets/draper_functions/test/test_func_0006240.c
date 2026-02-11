asn_parse_header(u_char * data, size_t * datalength, u_char * type)
{
    register u_char *bufp;
    u_long          asn_length;

    if (!data || !datalength || !type) {
        ERROR_MSG("parse header: NULL pointer");
        return NULL;
    }
    bufp = data;


    if (IS_EXTENSION_ID(*bufp)) {
        ERROR_MSG("can't process ID >= 30");
        return NULL;
    }
    *type = *bufp;
    bufp = asn_parse_length(bufp + 1, &asn_length);

    if (_asn_parse_length_check
        ("parse header", bufp, data, asn_length, *datalength))
        return NULL;

#ifdef DUMP_PRINT_HEADERS
    DEBUGDUMPSETUP("recv", data, (bufp - data));
    DEBUGMSG(("dumpv_recv", "  Header: 0x%.2X, len = %d (0x%X)\n", *data,
              asn_length, asn_length));
#else


#endif

#ifdef NETSNMP_WITH_OPAQUE_SPECIAL_TYPES

    if ((*type == ASN_OPAQUE) && (*bufp == ASN_OPAQUE_TAG1)) {


        switch (*(bufp + 1)) {
        case ASN_OPAQUE_COUNTER64:
        case ASN_OPAQUE_U64:
        case ASN_OPAQUE_FLOAT:
        case ASN_OPAQUE_DOUBLE:
        case ASN_OPAQUE_I64:
            *type = *(bufp + 1);
            break;

        default:


            *datalength = (int) asn_length;
            return bufp;
        }


        bufp = asn_parse_length(bufp + 2, &asn_length);
        if (_asn_parse_length_check("parse opaque header", bufp, data,
                                    asn_length, *datalength))
            return NULL;
    }
#endif

    *datalength = (int) asn_length;

    return bufp;
}
