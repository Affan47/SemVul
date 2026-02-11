asn_parse_unsigned_int(u_char * data,
                       size_t * datalength,
                       u_char * type, u_long * intp, size_t intsize)
{


    static const char *errpre = "parse uint";
    register u_char *bufp = data;
    u_long          asn_length;
    register u_long value = 0;

    if (intsize != sizeof(long)) {
        _asn_size_err(errpre, intsize, sizeof(long));
        return NULL;
    }
    *type = *bufp++;
    if (*type != ASN_COUNTER && *type != ASN_GAUGE && *type != ASN_TIMETICKS
            && *type != ASN_UINTEGER) {
        _asn_type_err(errpre, *type);
        return NULL;
    }
    bufp = asn_parse_length(bufp, &asn_length);
    if (_asn_parse_length_check
        (errpre, bufp, data, asn_length, *datalength))
        return NULL;

    if ((asn_length > (intsize + 1)) || ((int) asn_length == 0) ||
        ((asn_length == intsize + 1) && *bufp != 0x00)) {
        _asn_length_err(errpre, (size_t) asn_length, intsize);
        return NULL;
    }
    *datalength -= (int) asn_length + (bufp - data);
    if (*bufp & 0x80)
        value = ~value;

    DEBUGDUMPSETUP("recv", data, bufp - data + asn_length);

    while (asn_length--)
        value = (value << 8) | *bufp++;

    CHECK_OVERFLOW_U(value,2);

    DEBUGMSG(("dumpv_recv", "  UInteger:\t%ld (0x%.2lX)\n", value, value));

    *intp = value;
    return bufp;
}
