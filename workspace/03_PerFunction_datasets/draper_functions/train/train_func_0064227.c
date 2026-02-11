xmlSecInit(void) {
    xmlSecErrorsInit();
    xmlSecIOInit();

#ifndef XMLSEC_NO_CRYPTO_DYNAMIC_LOADING
    if(xmlSecCryptoDLInit() < 0) {
	xmlSecError(XMLSEC_ERRORS_HERE,
		    NULL,
		    "xmlSecCryptoDLInit",
		    XMLSEC_ERRORS_R_XMLSEC_FAILED,
		    XMLSEC_ERRORS_NO_MESSAGE);
	return(-1);
    }
#endif

    if(xmlSecKeyDataIdsInit() < 0) {
	xmlSecError(XMLSEC_ERRORS_HERE,
		    NULL,
		    "xmlSecKeyDataIdsInit",
		    XMLSEC_ERRORS_R_XMLSEC_FAILED,
		    XMLSEC_ERRORS_NO_MESSAGE);
	return(-1);
    }

    if(xmlSecTransformIdsInit() < 0) {
	xmlSecError(XMLSEC_ERRORS_HERE,
		    NULL,
		    "xmlSecTransformIdsInit",
		    XMLSEC_ERRORS_R_XMLSEC_FAILED,
		    XMLSEC_ERRORS_NO_MESSAGE);
	return(-1);
    }

#ifndef XMLSEC_NO_XKMS
    if(xmlSecXkmsRespondWithIdsInit() < 0) {
	xmlSecError(XMLSEC_ERRORS_HERE,
		    NULL,
		    "xmlSecXkmsRespondWithIdsInit",
		    XMLSEC_ERRORS_R_XMLSEC_FAILED,
		    XMLSEC_ERRORS_NO_MESSAGE);
	return(-1);
    }
    if(xmlSecXkmsServerRequestIdsInit() < 0) {
	xmlSecError(XMLSEC_ERRORS_HERE,
		    NULL,
		    "xmlSecXkmsServerRequestIdsInit",
		    XMLSEC_ERRORS_R_XMLSEC_FAILED,
		    XMLSEC_ERRORS_NO_MESSAGE);
	return(-1);
    }
#endif


    srand(time(NULL));
    return(0);
}
