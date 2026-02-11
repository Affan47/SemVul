xmlSecTmplSignatureAddReference(xmlNodePtr signNode, xmlSecTransformId digestMethodId,
                    const xmlChar *id, const xmlChar *uri, const xmlChar *type) {
    xmlNodePtr signedInfoNode;

    xmlSecAssert2(signNode != NULL, NULL);
    xmlSecAssert2(digestMethodId != NULL, NULL);
    xmlSecAssert2(digestMethodId->href != NULL, NULL);

    signedInfoNode = xmlSecFindChild(signNode, xmlSecNodeSignedInfo, xmlSecDSigNs);
    if(signedInfoNode == NULL) {
        xmlSecError(XMLSEC_ERRORS_HERE,
                    NULL,
                    xmlSecErrorsSafeString(xmlSecNodeSignedInfo),
                    XMLSEC_ERRORS_R_NODE_NOT_FOUND,
                    XMLSEC_ERRORS_NO_MESSAGE);
        return(NULL);
    }

    return(xmlSecTmplAddReference(signedInfoNode, digestMethodId, id, uri, type));
}
