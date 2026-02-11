nssTokenArray_Destroy (
  NSSToken **tokens
)
{
    if (tokens) {
	NSSToken **tokenp;
	for (tokenp = tokens; *tokenp; tokenp++) {
	    nssToken_Destroy(*tokenp);
	}
	nss_ZFreeIf(tokens);
    }
}
