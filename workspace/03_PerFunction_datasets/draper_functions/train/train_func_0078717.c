rsa2_openssh_fmtkey(void *key, unsigned char *blob, int len)
{
    struct RSAKey *rsa = (struct RSAKey *) key;
    int bloblen, i;

    bloblen =
	ssh2_bignum_length(rsa->modulus) +
	ssh2_bignum_length(rsa->exponent) +
	ssh2_bignum_length(rsa->private_exponent) +
	ssh2_bignum_length(rsa->iqmp) +
	ssh2_bignum_length(rsa->p) + ssh2_bignum_length(rsa->q);

    if (bloblen > len)
	return bloblen;

    bloblen = 0;
#define ENC(x) \
    PUT_32BIT(blob+bloblen, ssh2_bignum_length((x))-4); bloblen += 4; \
    for (i = ssh2_bignum_length((x))-4; i-- ;) blob[bloblen++]=bignum_byte((x),i);
    ENC(rsa->modulus);
    ENC(rsa->exponent);
    ENC(rsa->private_exponent);
    ENC(rsa->iqmp);
    ENC(rsa->p);
    ENC(rsa->q);

    return bloblen;
}
