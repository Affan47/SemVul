ssl3_SendNextProto(sslSocket *ss)
{
    SECStatus rv;
    int padding_len;
    static const unsigned char padding[32] = {0};

    if (ss->ssl3.nextProto.len == 0 ||
	ss->ssl3.nextProtoState == SSL_NEXT_PROTO_SELECTED) {
	return SECSuccess;
    }

    PORT_Assert( ss->opt.noLocks || ssl_HaveXmitBufLock(ss));
    PORT_Assert( ss->opt.noLocks || ssl_HaveSSL3HandshakeLock(ss));

    padding_len = 32 - ((ss->ssl3.nextProto.len + 2) % 32);

    rv = ssl3_AppendHandshakeHeader(ss, next_proto, ss->ssl3.nextProto.len +
						    2 + padding_len);
    if (rv != SECSuccess) {
	return rv;
    }
    rv = ssl3_AppendHandshakeVariable(ss, ss->ssl3.nextProto.data,
				      ss->ssl3.nextProto.len, 1);
    if (rv != SECSuccess) {
	return rv;
    }
    rv = ssl3_AppendHandshakeVariable(ss, padding, padding_len, 1);
    if (rv != SECSuccess) {
	return rv;
    }
    return rv;
}
