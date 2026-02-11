huffman_init(void)
{    	int tc, th, tt;
 	const unsigned char *ptr= JPEGHuffmanTable ;
	int i, j, l;
	l = JPG_HUFFMAN_TABLE_LENGTH ;
	    while (l > 0) {
		int hufflen[16], k;
		unsigned char huffvals[256];

		tc = *ptr++;
		th = tc & 15;
		tc >>= 4;
		tt = tc * 2 + th;
		if (tc > 1 || th > 1)
		    return -ERR_BAD_TABLES;
		for (i = 0; i < 16; i++)
		    hufflen[i] = *ptr++;
		l -= 1 + 16;
		k = 0;
		for (i = 0; i < 16; i++) {
		    for (j = 0; j < hufflen[i]; j++)
			huffvals[k++] = *ptr++;
		    l -= hufflen[i];
		}
		dec_makehuff(dhuff + tt, hufflen, huffvals);
	    }
	    return 0;
}
