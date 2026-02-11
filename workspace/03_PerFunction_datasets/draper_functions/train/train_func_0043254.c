ssl3_SendSupportedPointFormatsXtn(
                        sslSocket * ss,
                        PRBool      append,
                        PRUint32    maxBytes)
{
    if (!ss || !ssl3_IsECCEnabled(ss))
        return 0;
    if (append && maxBytes >= (sizeof ecPtFmt)) {
        SECStatus rv = ssl3_AppendHandshake(ss, ecPtFmt, (sizeof ecPtFmt));
        if (rv != SECSuccess)
            return -1;
        if (!ss->sec.isServer) {
            TLSExtensionData *xtnData = &ss->xtnData;
            xtnData->advertised[xtnData->numAdvertised++] =
                ssl_ec_point_formats_xtn;
        }
    }
    return (sizeof ecPtFmt);
}
