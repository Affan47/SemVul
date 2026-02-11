CERT_FindNameConstraintsExten(PLArenaPool      *arena,
                              CERTCertificate  *cert,
                              CERTNameConstraints **constraints)
{
    SECStatus            rv = SECSuccess;
    SECItem              constraintsExtension;
    void                *mark = NULL;

    *constraints = NULL;

    rv = CERT_FindCertExtension(cert, SEC_OID_X509_NAME_CONSTRAINTS,
                                &constraintsExtension);
    if (rv != SECSuccess) {
        if (PORT_GetError() == SEC_ERROR_EXTENSION_NOT_FOUND) {
            rv = SECSuccess;
        }
        return rv;
    }

    mark = PORT_ArenaMark(arena);

    *constraints = cert_DecodeNameConstraints(arena, &constraintsExtension);
    if (*constraints == NULL) {
        rv = SECFailure;
    }
    PORT_Free (constraintsExtension.data);

    if (rv == SECFailure) {
        PORT_ArenaRelease(arena, mark);
    } else {
        PORT_ArenaUnmark(arena, mark);
    }

    return rv;
}
