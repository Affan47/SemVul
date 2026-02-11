ssl3_AppendHandshakeVariable(
    sslSocket *ss, const SSL3Opaque *src, PRInt32 bytes, PRInt32 lenSize)
{
    SECStatus rv;

    PORT_Assert((bytes < (1<<8) && lenSize == 1) ||
	      (bytes < (1L<<16) && lenSize == 2) ||
	      (bytes < (1L<<24) && lenSize == 3));

    SSL_TRC(60,("%d: append variable:", SSL_GETPID()));
    rv = ssl3_AppendHandshakeNumber(ss, bytes, lenSize);
    if (rv != SECSuccess) {
	return rv;
    }
    SSL_TRC(60, ("data:"));
    rv = ssl3_AppendHandshake(ss, src, bytes);
    return rv;
}
