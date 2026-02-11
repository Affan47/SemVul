ssl3_ConsumeHandshakeNumber(sslSocket *ss, PRInt32 bytes, SSL3Opaque **b,
			    PRUint32 *length)
{
    PRUint8  *buf = *b;
    int       i;
    PRInt32   num = 0;

    PORT_Assert( ss->opt.noLocks || ssl_HaveRecvBufLock(ss) );
    PORT_Assert( ss->opt.noLocks || ssl_HaveSSL3HandshakeLock(ss) );
    PORT_Assert( bytes <= sizeof num);

    if ((PRUint32)bytes > *length) {
	return ssl3_DecodeError(ss);
    }
    PRINT_BUF(60, (ss, "consume bytes:", *b, bytes));

    for (i = 0; i < bytes; i++)
	num = (num << 8) + buf[i];
    *b      += bytes;
    *length -= bytes;
    return num;
}
