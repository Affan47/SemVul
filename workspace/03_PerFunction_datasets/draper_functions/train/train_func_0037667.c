RC4_CreateContext(const unsigned char *key, int len)
{
    RC4Context *cx = RC4_AllocateContext();
    if (cx) {
	SECStatus rv = RC4_InitContext(cx, key, len, NULL, 0, 0, 0);
	if (rv != SECSuccess) {
	    PORT_ZFree(cx, sizeof(*cx));
	    cx = NULL;
	}
    }
    return cx;
}
