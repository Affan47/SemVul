SECU_PrintRSAPublicKey(FILE *out, SECKEYPublicKey *pk, char *m, int level)
{
    SECU_Indent(out, level); fprintf(out, "%s:\n", m);
    SECU_PrintInteger(out, &pk->u.rsa.modulus, "Modulus", level+1);
    SECU_PrintInteger(out, &pk->u.rsa.publicExponent, "Exponent", level+1);
    if (pk->u.rsa.publicExponent.len == 1 &&
        pk->u.rsa.publicExponent.data[0] == 1) {
	SECU_Indent(out, level +1); fprintf(out, "Error: INVALID RSA KEY!\n");
    }
}
