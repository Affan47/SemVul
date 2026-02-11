ebcdic_to_multibyte_string(unsigned char *ebc, size_t ebc_len, char mb[],
	size_t mb_len)
{
    	int nmb = 0;

    	while (ebc_len && mb_len) {
	    	int xlen;

		xlen = ebcdic_to_multibyte(*ebc, mb, mb_len);
		if (xlen) {
		    	mb += xlen - 1;
			mb_len -= (xlen - 1);
			nmb += xlen - 1;
		}
		ebc++;
		ebc_len--;
	}
	return nmb;
}
