ssl3_ConsumeSignatureAndHashAlgorithm(sslSocket *ss,
				      SSL3Opaque **b,
				      PRUint32 *length,
				      SSL3SignatureAndHashAlgorithm *out)
{
    unsigned char bytes[2];
    SECStatus rv;

    rv = ssl3_ConsumeHandshake(ss, bytes, sizeof(bytes), b, length);
    if (rv != SECSuccess) {
	return rv;
    }

    out->hashAlg = ssl3_TLSHashAlgorithmToOID(bytes[0]);
    if (out->hashAlg == SEC_OID_UNKNOWN) {
	PORT_SetError(SSL_ERROR_UNSUPPORTED_HASH_ALGORITHM);
	return SECFailure;
    }

    out->sigAlg = bytes[1];
    return SECSuccess;
}
