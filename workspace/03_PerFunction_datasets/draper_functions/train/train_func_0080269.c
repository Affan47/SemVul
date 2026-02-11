crmf_encode_popoprivkey(PLArenaPool            *poolp,
			CRMFCertReqMsg         *inCertReqMsg,
			CRMFPOPOPrivKey        *popoPrivKey,
			const SEC_ASN1Template *privKeyTemplate)
{
    struct crmfEncoderArg   encoderArg;
    SECItem                 derTemp = { siBuffer, NULL, 0 };
    SECStatus               rv;
    void                   *mark;
    const SEC_ASN1Template *subDerTemplate;

    mark = PORT_ArenaMark(poolp);
    rv = crmf_init_encoder_callback_arg(&encoderArg, &derTemp);
    if (rv != SECSuccess) {
        goto loser;
    }
    subDerTemplate = crmf_get_popoprivkey_subtemplate(popoPrivKey);


    rv = SEC_ASN1Encode(&popoPrivKey->message.thisMessage,
			subDerTemplate,
			crmf_generic_encoder_callback, &encoderArg);
    if (rv != SECSuccess) {
        goto loser;
    }
    if (encoderArg.allocatedLen > derTemp.len+2) {
        void *dummy = PORT_Realloc(derTemp.data, derTemp.len+2);
	if (dummy == NULL) {
	    goto loser;
	}
	derTemp.data = dummy;
    }
    PORT_Memmove(&derTemp.data[2], &derTemp.data[0], derTemp.len);


    derTemp.data[0] = (unsigned char)privKeyTemplate->kind;
    derTemp.data[1] = (unsigned char)derTemp.len;
    derTemp.len += 2;
    rv = SECITEM_CopyItem(poolp, &inCertReqMsg->derPOP, &derTemp);
    if (rv != SECSuccess) {
        goto loser;
    }
    PORT_Free(derTemp.data);
    PORT_ArenaUnmark(poolp, mark);
    return SECSuccess;
 loser:
    PORT_ArenaRelease(poolp, mark);
    if (derTemp.data) {
        PORT_Free(derTemp.data);
    }
    return SECFailure;
}
