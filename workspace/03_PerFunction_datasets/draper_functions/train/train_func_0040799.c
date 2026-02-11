PEM_write_bio_X509(BIO *bp, X509 *x) {
   if (K_PEM_ASN1_write_bio) return (K_PEM_ASN1_write_bio) ((int (*)())K_i2d_X509, PEM_STRING_X509, bp, (char *)x, 0L, 0L, 0, 0L, 0L);
   else return -1;
}
