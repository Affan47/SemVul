xmlSecCryptoDLUnloadLibrary(const xmlChar* crypto) {
    xmlSecCryptoDLLibraryPtr lib;
    int pos;
    int ret;

    xmlSecAssert2(crypto != NULL, -1);

    pos = xmlSecCryptoDLLibrariesListFindByName(&gXmlSecCryptoDLLibraries, crypto);
    if(pos < 0) {

        return(0);
    }

    lib = (xmlSecCryptoDLLibraryPtr)xmlSecPtrListGetItem(&gXmlSecCryptoDLLibraries, pos);
    if((lib != NULL) && (lib->functions == gXmlSecCryptoDLFunctions)) {
        gXmlSecCryptoDLFunctions = NULL;
    }

    ret = xmlSecPtrListRemove(&gXmlSecCryptoDLLibraries, pos);
    if(ret < 0) {
        xmlSecError(XMLSEC_ERRORS_HERE,
                    NULL,
                    "xmlSecPtrListRemove",
                    XMLSEC_ERRORS_R_XMLSEC_FAILED,
                    XMLSEC_ERRORS_NO_MESSAGE);
        return(-1);
    }

    return(0);
}
