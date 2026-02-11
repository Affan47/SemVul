asn_parse_float(u_char * data,
                size_t * datalength,
                u_char * type, float *floatp, size_t floatsize)
{
    static const char *errpre = "parse float";
    register u_char *bufp = data;
    u_long          asn_length;
    union {
        float           floatVal;
        long            longVal;
        u_char          c[sizeof(float)];
    } fu;

    if (floatsize != sizeof(float)) {
        _asn_size_err("parse float", floatsize, sizeof(float));
        return NULL;
    }
    *type = *bufp++;
    bufp = asn_parse_length(bufp, &asn_length);
    if (_asn_parse_length_check("parse float", bufp, data,
                                asn_length, *datalength))
        return NULL;

    DEBUGDUMPSETUP("recv", data, bufp - data + asn_length);


    if ((*type == ASN_OPAQUE) &&
        (asn_length == ASN_OPAQUE_FLOAT_BER_LEN) &&
        (*bufp == ASN_OPAQUE_TAG1) && (*(bufp + 1) == ASN_OPAQUE_FLOAT)) {


        bufp = asn_parse_length(bufp + 2, &asn_length);
        if (_asn_parse_length_check("parse opaque float", bufp, data,
                                    asn_length, *datalength))
            return NULL;


        *type = ASN_OPAQUE_FLOAT;
    }

    if (*type != ASN_OPAQUE_FLOAT) {
        _asn_type_err(errpre, *type);
        return NULL;
    }

    if (asn_length != sizeof(float)) {
        _asn_size_err("parse seq float", asn_length, sizeof(float));
        return NULL;
    }

    *datalength -= (int) asn_length + (bufp - data);
    memcpy(&fu.c[0], bufp, asn_length);


    fu.longVal = ntohl(fu.longVal);

    *floatp = fu.floatVal;

    DEBUGMSG(("dumpv_recv", "Opaque float: %f\n", *floatp));
    return bufp;
}
