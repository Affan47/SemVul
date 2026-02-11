ssl3_ServerSendStatusRequestXtn(
                        sslSocket * ss,
                        PRBool      append,
                        PRUint32    maxBytes)
{
    PRInt32 extension_length;
    SECStatus rv;
    int i;
    PRBool haveStatus = PR_FALSE;

    for (i = kt_null; i < kt_kea_size; i++) {


        if (ss->certStatusArray[i] && ss->certStatusArray[i]->len) {
            haveStatus = PR_TRUE;
            break;
        }
    }
    if (!haveStatus)
        return 0;

    extension_length = 2 + 2;
    if (append && maxBytes >= extension_length) {

        rv = ssl3_AppendHandshakeNumber(ss, ssl_cert_status_xtn, 2);
        if (rv != SECSuccess)
            return -1;

        rv = ssl3_AppendHandshakeNumber(ss, 0, 2);
        if (rv != SECSuccess)
            return -1;
    }

    return extension_length;
}
