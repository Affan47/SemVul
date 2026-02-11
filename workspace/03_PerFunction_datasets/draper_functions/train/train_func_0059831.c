xmlSecGnuTLSAppKeysMngrCertLoad(xmlSecKeysMngrPtr mngr,
                                const char *filename,
                                xmlSecKeyDataFormat format,
                                xmlSecKeyDataType type) {
    xmlSecBuffer buffer;
    int ret;

    xmlSecAssert2(mngr != NULL, -1);
    xmlSecAssert2(filename != NULL, -1);
    xmlSecAssert2(format != xmlSecKeyDataFormatUnknown, -1);

    ret = xmlSecBufferInitialize(&buffer, 4*1024);
    if(ret < 0) {
        xmlSecError(XMLSEC_ERRORS_HERE,
                    NULL,
                    "xmlSecBufferInitialize",
                    XMLSEC_ERRORS_R_XMLSEC_FAILED,
                    XMLSEC_ERRORS_NO_MESSAGE);
        return(-1);
    }

    ret = xmlSecBufferReadFile(&buffer, filename);
    if((ret < 0) || (xmlSecBufferGetData(&buffer) == NULL) || (xmlSecBufferGetSize(&buffer) <= 0)) {
        xmlSecError(XMLSEC_ERRORS_HERE,
                    NULL,
                    "xmlSecBufferReadFile",
                    XMLSEC_ERRORS_R_XMLSEC_FAILED,
                    "filename=%s",
                    xmlSecErrorsSafeString(filename));
        xmlSecBufferFinalize(&buffer);
        return(-1);
    }

    ret = xmlSecGnuTLSAppKeysMngrCertLoadMemory(mngr,
                    xmlSecBufferGetData(&buffer),
                    xmlSecBufferGetSize(&buffer),
                    format,
                    type);
    if(ret < 0) {
        xmlSecError(XMLSEC_ERRORS_HERE,
                    NULL,
                    "xmlSecGnuTLSAppKeysMngrCertLoadMemory",
                    XMLSEC_ERRORS_R_XMLSEC_FAILED,
                    "filename=%s",
                    xmlSecErrorsSafeString(filename));
        xmlSecBufferFinalize(&buffer);
        return(-1);
    }


    xmlSecBufferFinalize(&buffer);
    return(0);
}
