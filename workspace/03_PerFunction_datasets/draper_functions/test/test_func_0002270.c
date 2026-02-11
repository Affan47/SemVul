NSS_CMSRecipientInfo_Encode(PLArenaPool* poolp,
                                      const NSSCMSRecipientInfo *src,
                                      SECItem* returned)
{
    extern const SEC_ASN1Template NSSCMSRecipientInfoTemplate[];
    SECStatus rv = SECFailure;
    if (!src || !returned) {
        PORT_SetError(SEC_ERROR_INVALID_ARGS);
    } else if (SEC_ASN1EncodeItem(poolp, returned, src,
        NSSCMSRecipientInfoTemplate))   {
        rv = SECSuccess;
    }
    return rv;
}
