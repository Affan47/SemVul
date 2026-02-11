dec_makehuff(hu, hufflen, huffvals)
struct dec_hufftbl *hu;
int *hufflen;
unsigned char *huffvals;
{
    int code, k, i, j, d, x, c, v;
    for (i = 0; i < (1 << DECBITS); i++)
	hu->llvals[i] = 0;


    code = 0;
    k = 0;
    for (i = 0; i < 16; i++, code <<= 1) {
	hu->valptr[i] = k;
	for (j = 0; j < hufflen[i]; j++) {
	    hu->vals[k] = *huffvals++;
	    if (i < DECBITS) {
		c = code << (DECBITS - 1 - i);
		v = hu->vals[k] & 0x0f;
		for (d = 1 << (DECBITS - 1 - i); --d >= 0;) {
		    if (v + i < DECBITS) {
			x = d >> (DECBITS - 1 - v - i);
			if (v && x < (1 << (v - 1)))
			    x += (-1 << v) + 1;
			x = x << 16 | (hu->vals[k] & 0xf0) << 4 |
			    (DECBITS - (i + 1 + v)) | 128;
		    } else
			x = v << 16 | (hu->vals[k] & 0xf0) << 4 |
			    (DECBITS - (i + 1));
		    hu->llvals[c | d] = x;
		}
	    }
	    code++;
	    k++;
	}
	hu->maxcode[i] = code;
    }
    hu->maxcode[16] = 0x20000;
}
