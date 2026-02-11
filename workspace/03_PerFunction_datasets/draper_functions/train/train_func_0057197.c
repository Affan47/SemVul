SECU_cert_fetchOID(SECOidTag *data, const SECOidData *src)
{
    if (*data == SEC_OID_UNKNOWN) {


        *data = SECOID_AddEntry(src);
    }
}
