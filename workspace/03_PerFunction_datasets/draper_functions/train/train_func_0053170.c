xmlSecPrintXmlString(FILE * fd, const xmlChar * str) {
    int res;

    if(str != NULL) {
        xmlChar * encoded_str = NULL;
        encoded_str = xmlEncodeSpecialChars(NULL, str);
        if(encoded_str == NULL) {
            xmlSecError(XMLSEC_ERRORS_HERE,
                        NULL,
                        "xmlEncodeSpecialChars",
                        XMLSEC_ERRORS_R_XML_FAILED,
                        "string=%s",
                        xmlSecErrorsSafeString(str));
            return(-1);
        }

        res = fprintf(fd, "%s", (const char*)encoded_str);
        xmlFree(encoded_str);
    } else {
        res = fprintf(fd, "NULL");
    }

    if(res < 0) {
        xmlSecError(XMLSEC_ERRORS_HERE,
                    NULL,
                    "fprintf",
                    XMLSEC_ERRORS_R_IO_FAILED,
                    "res=%d,errno=%d",
                    res, errno);
        return(-1);
    }
    return(res);
}
