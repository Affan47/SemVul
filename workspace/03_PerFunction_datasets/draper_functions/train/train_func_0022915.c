SECU_PrintCertificate(FILE *out, const SECItem *der, const char *m, int level)
{
    PLArenaPool *arena = PORT_NewArena(DER_DEFAULT_CHUNKSIZE);
    CERTCertificate *c;
    int rv = SEC_ERROR_NO_MEMORY;
    int iv;

    if (!arena)
	return rv;


    c = PORT_ArenaZNew(arena, CERTCertificate);
    if (!c)
	goto loser;
    c->arena = arena;
    rv = SEC_ASN1DecodeItem(arena, c,
                            SEC_ASN1_GET(CERT_CertificateTemplate), der);
    if (rv) {
        SECU_Indent(out, level);
	SECU_PrintErrMsg(out, level, "Error", "Parsing extension");
	SECU_PrintAny(out, der, "Raw", level);
	goto loser;
    }

    SECU_Indent(out, level); fprintf(out, "%s:\n", m);
    iv = c->version.len ? DER_GetInteger(&c->version) : 0;
    SECU_Indent(out, level+1); fprintf(out, "%s: %d (0x%x)\n", "Version", iv + 1, iv);

    SECU_PrintInteger(out, &c->serialNumber, "Serial Number", level+1);
    SECU_PrintAlgorithmID(out, &c->signature, "Signature Algorithm", level+1);
    SECU_PrintName(out, &c->issuer, "Issuer", level+1);
    if (!SECU_GetWrapEnabled())
	SECU_Newline(out);
    secu_PrintValidity(out, &c->validity, "Validity", level+1);
    SECU_PrintName(out, &c->subject, "Subject", level+1);
    if (!SECU_GetWrapEnabled())
	SECU_Newline(out);
    secu_PrintSubjectPublicKeyInfo(out, arena, &c->subjectPublicKeyInfo,
			      "Subject Public Key Info", level+1);
    if (c->issuerID.data)
	secu_PrintDecodedBitString(out, &c->issuerID, "Issuer Unique ID", level+1);
    if (c->subjectID.data)
	secu_PrintDecodedBitString(out, &c->subjectID, "Subject Unique ID", level+1);
    SECU_PrintExtensions(out, c->extensions, "Signed Extensions", level+1);
loser:
    PORT_FreeArena(arena, PR_FALSE);
    return rv;
}
