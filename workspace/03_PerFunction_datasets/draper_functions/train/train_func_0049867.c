ossl_ocspcid_cmp_issuer(VALUE self, VALUE other)
{
    OCSP_CERTID *id, *id2;
    int result;

    GetOCSPCertId(self, id);
    SafeGetOCSPCertId(other, id2);
    result = OCSP_id_issuer_cmp(id, id2);

    return (result == 0) ? Qtrue : Qfalse;
}
