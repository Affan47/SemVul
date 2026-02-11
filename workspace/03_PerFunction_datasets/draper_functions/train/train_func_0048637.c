ASN1_INTEGER_QString(ASN1_INTEGER *aint) {
char *rep = KOSSL::self()->i2s_ASN1_INTEGER(NULL, aint);
QString yy = rep;
KOSSL::self()->OPENSSL_free(rep);
return yy;
}
