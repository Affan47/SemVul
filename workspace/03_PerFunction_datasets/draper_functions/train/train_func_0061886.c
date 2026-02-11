ocsp_DecodeBasicOCSPResponse(PLArenaPool *arena, SECItem *src)
{
    void *mark;
    ocspBasicOCSPResponse *basicResponse;
    ocspResponseData *responseData;
    ocspResponderID *responderID;
    CERTOCSPResponderIDType responderIDType;
    const SEC_ASN1Template *responderIDTemplate;
    int derTag;
    SECStatus rv;
    SECItem newsrc;

    mark = PORT_ArenaMark(arena);

    basicResponse = PORT_ArenaZAlloc(arena, sizeof(ocspBasicOCSPResponse));
    if (basicResponse == NULL) {
	goto loser;
    }


    rv = SECITEM_CopyItem(arena, &newsrc, src);
    if ( rv != SECSuccess ) {
	goto loser;
    }

    rv = SEC_QuickDERDecodeItem(arena, basicResponse,
			    ocsp_BasicOCSPResponseTemplate, &newsrc);
    if (rv != SECSuccess) {
	if (PORT_GetError() == SEC_ERROR_BAD_DER)
	    PORT_SetError(SEC_ERROR_OCSP_MALFORMED_RESPONSE);
	goto loser;
    }

    responseData = basicResponse->tbsResponseData;


    PORT_Assert(responseData != NULL);
    PORT_Assert(responseData->derResponderID.data != NULL);


    derTag = responseData->derResponderID.data[0] & SEC_ASN1_TAGNUM_MASK;
    responderIDType = ocsp_ResponderIDTypeByTag(derTag);
    responderIDTemplate = ocsp_ResponderIDTemplateByType(responderIDType);

    responderID = PORT_ArenaZAlloc(arena, sizeof(ocspResponderID));
    if (responderID == NULL) {
	goto loser;
    }

    rv = SEC_QuickDERDecodeItem(arena, responderID, responderIDTemplate,
			    &responseData->derResponderID);
    if (rv != SECSuccess) {
	if (PORT_GetError() == SEC_ERROR_BAD_DER)
	    PORT_SetError(SEC_ERROR_OCSP_MALFORMED_RESPONSE);
	goto loser;
    }

    responderID->responderIDType = responderIDType;
    responseData->responderID = responderID;


    rv = ocsp_FinishDecodingSingleResponses(arena, responseData->responses);
    if (rv != SECSuccess) {
	goto loser;
    }

    PORT_ArenaUnmark(arena, mark);
    return basicResponse;

loser:
    PORT_ArenaRelease(arena, mark);
    return NULL;
}
