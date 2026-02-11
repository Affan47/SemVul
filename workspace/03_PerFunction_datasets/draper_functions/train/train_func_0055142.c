cert_GetLogFromVerifyNode(
    CERTVerifyLog *log,
    PKIX_VerifyNode *node,
    void *plContext)
{
    PKIX_List       *children = NULL;
    PKIX_VerifyNode *childNode = NULL;

    PKIX_ENTER(CERTVFYPKIX, "cert_GetLogFromVerifyNode");

    children = node->children;

    if (children == NULL) {
        PKIX_ERRORCODE errCode = PKIX_ANCHORDIDNOTCHAINTOCERT;
        if (node->error && node->error->errCode != errCode) {
#ifdef DEBUG_volkov
            char *string = pkix_Error2ASCII(node->error, plContext);
            fprintf(stderr, "Branch search finished with error: \t%s\n", string);
            PKIX_PL_Free(string, NULL);
#endif
            if (log != NULL) {
                SECErrorCodes nssErrorCode = 0;
                CERTCertificate *cert = NULL;

                cert = node->verifyCert->nssCert;

                PKIX_CHECK(
                    cert_PkixErrorToNssCode(node->error, &nssErrorCode,
                                            plContext),
                    PKIX_GETPKIXERRORCODEFAILED);

                cert_AddToVerifyLog(log, cert, nssErrorCode, node->depth, NULL);
            }
        }
        PKIX_RETURN(CERTVFYPKIX);
    } else {
        PRUint32      i = 0;
        PKIX_UInt32   length = 0;

        PKIX_CHECK(
            PKIX_List_GetLength(children, &length, plContext),
            PKIX_LISTGETLENGTHFAILED);

        for (i = 0; i < length; i++){

            PKIX_CHECK(
                PKIX_List_GetItem(children, i, (PKIX_PL_Object**)&childNode,
                                  plContext),
                PKIX_LISTGETITEMFAILED);

            PKIX_CHECK(
                cert_GetLogFromVerifyNode(log, childNode, plContext),
                PKIX_ERRORINRECURSIVEEQUALSCALL);

            PKIX_DECREF(childNode);
        }
    }

cleanup:
    PKIX_DECREF(childNode);

    PKIX_RETURN(CERTVFYPKIX);
}
