xmlSecNssKWAesSetKey(xmlSecTransformPtr transform, xmlSecKeyPtr key) {
    xmlSecBufferPtr buffer;
    xmlSecSize keySize;
    xmlSecSize expectedKeySize;
    int ret;

    xmlSecAssert2(xmlSecNssKWAesCheckId(transform), -1);
    xmlSecAssert2((transform->operation == xmlSecTransformOperationEncrypt) || (transform->operation == xmlSecTransformOperationDecrypt), -1);
    xmlSecAssert2(xmlSecTransformCheckSize(transform, xmlSecNssKWAesSize), -1);
    xmlSecAssert2(xmlSecNssKWAesGetKey(transform) != NULL, -1);
    xmlSecAssert2(key != NULL, -1);
    xmlSecAssert2(xmlSecKeyDataCheckId(xmlSecKeyGetValue(key), xmlSecNssKeyDataAesId), -1);

    buffer = xmlSecKeyDataBinaryValueGetBuffer(xmlSecKeyGetValue(key));
    xmlSecAssert2(buffer != NULL, -1);

    keySize = xmlSecBufferGetSize(buffer);
    expectedKeySize = xmlSecNssKWAesGetKeySize(transform);
    if(keySize < expectedKeySize) {
	xmlSecError(XMLSEC_ERRORS_HERE,
		    xmlSecErrorsSafeString(xmlSecTransformGetName(transform)),
		    NULL,
		    XMLSEC_ERRORS_R_INVALID_KEY_DATA_SIZE,
		    "key=%d;expected=%d",
		    keySize, expectedKeySize);
	return(-1);
    }

    ret = xmlSecBufferSetData(xmlSecNssKWAesGetKey(transform),
			    xmlSecBufferGetData(buffer),
			    expectedKeySize);
    if(ret < 0) {
	xmlSecError(XMLSEC_ERRORS_HERE,
		    xmlSecErrorsSafeString(xmlSecTransformGetName(transform)),
		    "xmlSecBufferSetData",
		    XMLSEC_ERRORS_R_XMLSEC_FAILED,
		    "expected-size=%d", expectedKeySize);
	return(-1);
    }

    return(0);
}
