SECU_PrintDumpDerIssuerAndSerial(FILE *out, SECItem *der, char *m,
                                 int level)
{
    PLArenaPool *arena = PORT_NewArena(DER_DEFAULT_CHUNKSIZE);
    CERTCertificate *c;
    int rv = SEC_ERROR_NO_MEMORY;
    char *derIssuerB64;
    char *derSerialB64;

    if (!arena)
        return rv;


    c = PORT_ArenaZNew(arena, CERTCertificate);
    if (!c)
        goto loser;
    c->arena = arena;
    rv = SEC_ASN1DecodeItem(arena, c,
                            SEC_ASN1_GET(CERT_CertificateTemplate), der);
    if (rv) {
        SECU_PrintErrMsg(out, 0, "Error", "Parsing extension");
        goto loser;
    }

    SECU_PrintName(out, &c->subject, "Subject", 0);
    if (!SECU_GetWrapEnabled())
	SECU_Newline(out);
    SECU_PrintName(out, &c->issuer, "Issuer", 0);
    if (!SECU_GetWrapEnabled())
	SECU_Newline(out);
    SECU_PrintInteger(out, &c->serialNumber, "Serial Number", 0);

    derIssuerB64 = BTOA_ConvertItemToAscii(&c->derIssuer);
    derSerialB64 = BTOA_ConvertItemToAscii(&c->serialNumber);

    fprintf(out, "Issuer DER Base64:\n");
    if (SECU_GetWrapEnabled()) {
	fprintf(out, "%s\n", derIssuerB64);
    } else {
	printStringWithoutCRLF(out, derIssuerB64);
	fputs("\n", out);
    }

    fprintf(out, "Serial DER Base64:\n");
    if (SECU_GetWrapEnabled()) {
	fprintf(out, "%s\n", derSerialB64);
    } else {
	printStringWithoutCRLF(out, derSerialB64);
	fputs("\n", out);
    }

    PORT_Free(derIssuerB64);
    PORT_Free(derSerialB64);

    fprintf(out, "Serial DER as C source: \n{ %d, \"", c->serialNumber.len);

    {
      int i;
      for (i=0; i < c->serialNumber.len; ++i) {
        unsigned char *chardata = (unsigned char*)(c->serialNumber.data);
        unsigned char c = *(chardata + i);

        fprintf(out, "\\x%02x", c);
      }
      fprintf(out, "\" }\n");
    }

loser:
    PORT_FreeArena(arena, PR_FALSE);
    return rv;
}
