sec_pkcs12_decoder_safe_bag_notify(void *arg, PRBool before,
				   void *dest, int real_depth)
{
    sec_PKCS12SafeContentsContext *safeContentsCtx =
        (sec_PKCS12SafeContentsContext *)arg;
    SEC_PKCS12DecoderContext *p12dcx;
    sec_PKCS12SafeBag *bag;
    PRBool after;


    if(!safeContentsCtx || !safeContentsCtx->p12dcx ||
		safeContentsCtx->p12dcx->error) {
	return;
    }
    p12dcx = safeContentsCtx->p12dcx;


    if(before)
	after = PR_FALSE;
    else
	after = PR_TRUE;


    bag = safeContentsCtx->currentSafeBag;
    if(bag->bagTypeTag == NULL) {
	if(after && (dest == &(bag->safeBagType))) {
	    bag->bagTypeTag = SECOID_FindOID(&(bag->safeBagType));
	    if(bag->bagTypeTag == NULL) {
		p12dcx->error = PR_TRUE;
		p12dcx->errorValue = SEC_ERROR_PKCS12_CORRUPT_PFX_STRUCTURE;
	    }
	}
	return;
    }


    switch(bag->bagTypeTag->offset) {
	case SEC_OID_PKCS12_V1_KEY_BAG_ID:
	case SEC_OID_PKCS12_V1_CERT_BAG_ID:
	case SEC_OID_PKCS12_V1_PKCS8_SHROUDED_KEY_BAG_ID:
	    break;
	case SEC_OID_PKCS12_V1_SAFE_CONTENTS_BAG_ID:


	    if(before && (dest == &(bag->safeBagContent))) {
		sec_pkcs12_decoder_begin_nested_safe_contents(safeContentsCtx);
	    } else if(after && (dest == &(bag->safeBagContent))) {

		sec_pkcs12_decoder_finish_nested_safe_contents(safeContentsCtx);
	    }
	    break;
	case SEC_OID_PKCS12_V1_CRL_BAG_ID:
	case SEC_OID_PKCS12_V1_SECRET_BAG_ID:
	default:

	    safeContentsCtx->skipCurrentSafeBag = PR_TRUE;
	    break;
    }

    return;
}
