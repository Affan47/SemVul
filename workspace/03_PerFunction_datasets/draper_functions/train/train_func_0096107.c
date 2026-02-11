xmlSecTmplTransformAddXPath2(xmlNodePtr transformNode, const xmlChar* type,
                        const xmlChar *expression, const xmlChar **nsList) {
    xmlNodePtr xpathNode;

    xmlSecAssert2(transformNode != NULL, -1);
    xmlSecAssert2(type != NULL, -1);
    xmlSecAssert2(expression != NULL, -1);

    xpathNode = xmlSecAddChild(transformNode, xmlSecNodeXPath, xmlSecXPath2Ns);
    if(xpathNode == NULL) {
        xmlSecError(XMLSEC_ERRORS_HERE,
                    NULL,
                    "xmlSecAddChild",
                    XMLSEC_ERRORS_R_XMLSEC_FAILED,
                    "node=%s",
                    xmlSecErrorsSafeString(xmlSecNodeXPath));
        return(-1);
    }
    xmlSetProp(xpathNode, xmlSecAttrFilter, type);

    xmlSecNodeEncodeAndSetContent(xpathNode, expression);
    return((nsList != NULL) ? xmlSecTmplNodeWriteNsList(xpathNode, nsList) : 0);
}
