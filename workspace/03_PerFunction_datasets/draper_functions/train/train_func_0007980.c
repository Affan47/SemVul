xmlSecOpenSSLX509CertDebugXmlDump(X509* cert, FILE* output) {
    char buf[1024];
    BIGNUM *bn = NULL;

    xmlSecAssert(cert != NULL);
    xmlSecAssert(output != NULL);

    fprintf(output, "<SubjectName>");
    xmlSecPrintXmlString(output,
        BAD_CAST X509_NAME_oneline(X509_get_subject_name(cert), buf, sizeof(buf))
    );
    fprintf(output, "</SubjectName>\n");


    fprintf(output, "<IssuerName>");
    xmlSecPrintXmlString(output,
        BAD_CAST X509_NAME_oneline(X509_get_issuer_name(cert), buf, sizeof(buf)));
    fprintf(output, "</IssuerName>\n");

    fprintf(output, "<SerialNumber>");
    bn = ASN1_INTEGER_to_BN(X509_get_serialNumber(cert),NULL);
    if(bn != NULL) {
        BN_print_fp(output, bn);
        BN_free(bn);
    }
    fprintf(output, "</SerialNumber>\n");
}
