asn_parse_double(u_char * data,
                 size_t * datalength,
                 u_char * type, double *doublep, size_t doublesize)
{
    static const char *errpre = "parse double";
    register u_char *bufp = data;
    u_long          asn_length;
    long            tmp;
    union {
        double          doubleVal;
        int             intVal[2];
        u_char          c[sizeof(double)];
    } fu;


    if (doublesize != sizeof(double)) {
        _asn_size_err("parse double", doublesize, sizeof(double));
        return NULL;
    }
    *type = *bufp++;
    bufp = asn_parse_length(bufp, &asn_length);
    if (_asn_parse_length_check("parse double", bufp, data,
                                asn_length, *datalength))
        return NULL;

    DEBUGDUMPSETUP("recv", data, bufp - data + asn_length);


    if ((*type == ASN_OPAQUE) &&
        (asn_length == ASN_OPAQUE_DOUBLE_BER_LEN) &&
        (*bufp == ASN_OPAQUE_TAG1) && (*(bufp + 1) == ASN_OPAQUE_DOUBLE)) {


        bufp = asn_parse_length(bufp + 2, &asn_length);
        if (_asn_parse_length_check("parse opaque double", bufp, data,
                                    asn_length, *datalength))
            return NULL;


        *type = ASN_OPAQUE_DOUBLE;
    }

    if (*type != ASN_OPAQUE_DOUBLE) {
        _asn_type_err(errpre, *type);
        return NULL;
    }

    if (asn_length != sizeof(double)) {
        _asn_size_err("parse seq double", asn_length, sizeof(double));
        return NULL;
    }
    *datalength -= (int) asn_length + (bufp - data);
    memcpy(&fu.c[0], bufp, asn_length);


    tmp = ntohl(fu.intVal[0]);
    fu.intVal[0] = ntohl(fu.intVal[1]);
    fu.intVal[1] = tmp;

    *doublep = fu.doubleVal;
    DEBUGMSG(("dumpv_recv", "  Opaque Double:\t%f\n", *doublep));

    return bufp;
}
