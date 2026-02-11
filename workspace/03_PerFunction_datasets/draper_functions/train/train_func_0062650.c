p12u_ucs2_ascii_conversion_function(PRBool	   toUnicode,
				    unsigned char *inBuf,
				    unsigned int   inBufLen,
				    unsigned char *outBuf,
				    unsigned int   maxOutBufLen,
				    unsigned int  *outBufLen,
				    PRBool	   swapBytes)
{
    SECItem it = { 0 };
    SECItem *dup = NULL;
    PRBool ret;

#ifdef DEBUG_CONVERSION
    if (pk12_debugging) {
	int i;
	printf("Converted from:\n");
	for (i=0; i<inBufLen; i++) {
	    printf("%2x ", inBuf[i]);

	}
	printf("\n");
    }
#endif
    it.data = inBuf;
    it.len = inBufLen;
    dup = SECITEM_DupItem(&it);


    if (!toUnicode && swapBytes) {
	if (p12u_SwapUnicodeBytes(dup) != SECSuccess) {
	    SECITEM_ZfreeItem(dup, PR_TRUE);
	    return PR_FALSE;
	}
    }

    ret = PORT_UCS2_UTF8Conversion(toUnicode, dup->data, dup->len,
                                   outBuf, maxOutBufLen, outBufLen);
    if (dup)
	SECITEM_ZfreeItem(dup, PR_TRUE);

#ifdef DEBUG_CONVERSION
    if (pk12_debugging) {
	int i;
	printf("Converted to:\n");
	for (i=0; i<*outBufLen; i++) {
	    printf("%2x ", outBuf[i]);

	}
	printf("\n");
    }
#endif
    return ret;
}
