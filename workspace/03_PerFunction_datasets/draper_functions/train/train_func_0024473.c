cert_FindExtension(CERTCertExtension **extensions, int tag, SECItem *value)
{
    SECOidData *oid;

    oid = SECOID_FindOIDByTag((SECOidTag)tag);
    if ( !oid ) {
	return(SECFailure);
    }

    return(cert_FindExtensionByOID(extensions, &oid->oid, value));
}
