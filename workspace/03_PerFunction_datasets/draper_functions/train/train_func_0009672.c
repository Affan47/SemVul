secu_PrintSignedDataSigOpt(FILE *out, SECItem *der, const char *m,
			   int level, SECU_PPFunc inner,
                           SignatureOptionType withSignature)
{
    PLArenaPool *arena = PORT_NewArena(DER_DEFAULT_CHUNKSIZE);
    CERTSignedData *sd;
    int rv = SEC_ERROR_NO_MEMORY;

    if (!arena)
	return rv;


    sd = PORT_ArenaZNew(arena, CERTSignedData);
    if (!sd)
	goto loser;

    rv = SEC_ASN1DecodeItem(arena, sd, SEC_ASN1_GET(CERT_SignedDataTemplate),
                            der);
    if (rv)
	goto loser;

    if (m) {
        SECU_Indent(out, level); fprintf(out, "%s:\n", m);
    } else {
        level -= 1;
    }
    rv = (*inner)(out, &sd->data, "Data", level+1);

    if (withSignature) {
        SECU_PrintAlgorithmID(out, &sd->signatureAlgorithm, "Signature Algorithm",
                              level+1);
        DER_ConvertBitString(&sd->signature);
        SECU_PrintAsHex(out, &sd->signature, "Signature", level+1);
    }
    SECU_PrintFingerprints(out, der, "Fingerprint", level+1);
loser:
    PORT_FreeArena(arena, PR_FALSE);
    return rv;
}
