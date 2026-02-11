sec_pkcs12_bagHasKey(SEC_PKCS12DecoderContext *p12dcx, sec_PKCS12SafeBag *bag)
{
    int i;
    SECItem *keyId;
    SECItem *certKeyId;

    certKeyId = sec_pkcs12_get_attribute_value(bag, SEC_OID_PKCS9_LOCAL_KEY_ID);
    if (certKeyId == NULL) {
        return PR_FALSE;
    }

    for (i=0; p12dcx->keyList && p12dcx->keyList[i]; i++) {
        keyId = sec_pkcs12_get_attribute_value(p12dcx->keyList[i],
                                                SEC_OID_PKCS9_LOCAL_KEY_ID);
        if(!keyId) {
            continue;
        }
        if(SECITEM_CompareItem(certKeyId, keyId) == SECEqual) {
            return PR_TRUE;
        }
    }
    return PR_FALSE;
}
