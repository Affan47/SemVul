xmlSecKeyDataBinaryValueBinRead(xmlSecKeyDataId id, xmlSecKeyPtr key,
                                const xmlSecByte* buf, xmlSecSize bufSize,
                                xmlSecKeyInfoCtxPtr keyInfoCtx) {
    xmlSecKeyDataPtr data;
    int ret;

    xmlSecAssert2(id != xmlSecKeyDataIdUnknown, -1);
    xmlSecAssert2(key != NULL, -1);
    xmlSecAssert2(buf != NULL, -1);
    xmlSecAssert2(bufSize > 0, -1);
    xmlSecAssert2(keyInfoCtx != NULL, -1);


    data = xmlSecKeyGetValue(key);
    if(data != NULL) {
        xmlSecBufferPtr buffer;

        if(!xmlSecKeyDataCheckId(data, id)) {
            xmlSecError(XMLSEC_ERRORS_HERE,
                        xmlSecErrorsSafeString(xmlSecKeyDataKlassGetName(id)),
                        xmlSecErrorsSafeString(xmlSecKeyDataGetName(data)),
                        XMLSEC_ERRORS_R_KEY_DATA_ALREADY_EXIST,
                        XMLSEC_ERRORS_NO_MESSAGE);
            return(-1);
        }

        buffer = xmlSecKeyDataBinaryValueGetBuffer(data);
        if((buffer != NULL) && ((xmlSecSize)xmlSecBufferGetSize(buffer) != bufSize)) {
            xmlSecError(XMLSEC_ERRORS_HERE,
                        xmlSecErrorsSafeString(xmlSecKeyDataKlassGetName(id)),
                        xmlSecErrorsSafeString(xmlSecKeyDataGetName(data)),
                        XMLSEC_ERRORS_R_KEY_DATA_ALREADY_EXIST,
                        "cur-data-size=%d;new-data-size=%d",
                        xmlSecBufferGetSize(buffer), bufSize);
            return(-1);
        }
        if((buffer != NULL) && (bufSize > 0) && (memcmp(xmlSecBufferGetData(buffer), buf, bufSize) != 0)) {
            xmlSecError(XMLSEC_ERRORS_HERE,
                        xmlSecErrorsSafeString(xmlSecKeyDataKlassGetName(id)),
                        xmlSecErrorsSafeString(xmlSecKeyDataGetName(data)),
                        XMLSEC_ERRORS_R_KEY_DATA_ALREADY_EXIST,
                        "key already has a different value");
            return(-1);
        }
        if(buffer != NULL) {

            return(0);
        }


    }

    data = xmlSecKeyDataCreate(id);
    if(data == NULL ) {
        xmlSecError(XMLSEC_ERRORS_HERE,
                    xmlSecErrorsSafeString(xmlSecKeyDataKlassGetName(id)),
                    "xmlSecKeyDataCreate",
                    XMLSEC_ERRORS_R_XMLSEC_FAILED,
                    XMLSEC_ERRORS_NO_MESSAGE);
        return(-1);
    }

    ret = xmlSecKeyDataBinaryValueSetBuffer(data, buf, bufSize);
    if(ret < 0) {
        xmlSecError(XMLSEC_ERRORS_HERE,
                    xmlSecErrorsSafeString(xmlSecKeyDataKlassGetName(id)),
                    "xmlSecKeyDataBinaryValueSetBuffer",
                    XMLSEC_ERRORS_R_XMLSEC_FAILED,
                    "size=%d", bufSize);
        xmlSecKeyDataDestroy(data);
        return(-1);
    }

    if(xmlSecKeyReqMatchKeyValue(&(keyInfoCtx->keyReq), data) != 1) {
        xmlSecError(XMLSEC_ERRORS_HERE,
                    xmlSecErrorsSafeString(xmlSecKeyDataKlassGetName(id)),
                    "xmlSecKeyReqMatchKeyValue",
                    XMLSEC_ERRORS_R_XMLSEC_FAILED,
                    XMLSEC_ERRORS_NO_MESSAGE);
        xmlSecKeyDataDestroy(data);
        return(0);
    }

    ret = xmlSecKeySetValue(key, data);
    if(ret < 0) {
        xmlSecError(XMLSEC_ERRORS_HERE,
                    xmlSecErrorsSafeString(xmlSecKeyDataKlassGetName(id)),
                    "xmlSecKeySetValue",
                    XMLSEC_ERRORS_R_XMLSEC_FAILED,
                    XMLSEC_ERRORS_NO_MESSAGE);
        xmlSecKeyDataDestroy(data);
        return(-1);
    }

    return(0);
}
