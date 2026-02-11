xmlSecNssKWAesSetKeyReq(xmlSecTransformPtr transform,  xmlSecKeyReqPtr keyReq) {
    xmlSecAssert2(xmlSecNssKWAesCheckId(transform), -1);
    xmlSecAssert2((transform->operation == xmlSecTransformOperationEncrypt) || (transform->operation == xmlSecTransformOperationDecrypt), -1);
    xmlSecAssert2(xmlSecTransformCheckSize(transform, xmlSecNssKWAesSize), -1);
    xmlSecAssert2(keyReq != NULL, -1);

    keyReq->keyId 	 = xmlSecNssKeyDataAesId;
    keyReq->keyType  = xmlSecKeyDataTypeSymmetric;
    if(transform->operation == xmlSecTransformOperationEncrypt) {
	keyReq->keyUsage = xmlSecKeyUsageEncrypt;
    } else {
	keyReq->keyUsage = xmlSecKeyUsageDecrypt;
    }
    keyReq->keyBitsSize = 8 * xmlSecNssKWAesGetKeySize(transform);

    return(0);
}
