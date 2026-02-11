xmlSecCryptoAppKeysMngrCertLoad(xmlSecKeysMngrPtr mngr, const char *filename,
                                xmlSecKeyDataFormat format, xmlSecKeyDataType type) {
    if((xmlSecCryptoDLGetFunctions() == NULL) || (xmlSecCryptoDLGetFunctions()->cryptoAppKeysMngrCertLoad == NULL)) {
        xmlSecError(XMLSEC_ERRORS_HERE,
                    NULL,
                    "cryptoAppKeysMngrCertLoad",
                    XMLSEC_ERRORS_R_NOT_IMPLEMENTED,
                    XMLSEC_ERRORS_NO_MESSAGE);
        return(-1);
    }

    return(xmlSecCryptoDLGetFunctions()->cryptoAppKeysMngrCertLoad(mngr, filename, format, type));
}
