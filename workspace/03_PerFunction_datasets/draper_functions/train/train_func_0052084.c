CERT_EncodeIA5TypeExtension(PLArenaPool *arena, char *value, SECItem *encodedValue)
{
    SECItem encodeContext;
    SECStatus rv = SECSuccess;


    PORT_Memset (&encodeContext, 0, sizeof (encodeContext));

    if (value != NULL) {
	encodeContext.data = (unsigned char *)value;
	encodeContext.len = strlen(value);
    }
    if (SEC_ASN1EncodeItem (arena, encodedValue, &encodeContext,
			    CERTIA5TypeTemplate) == NULL) {
	rv = SECFailure;
    }

    return(rv);
}
