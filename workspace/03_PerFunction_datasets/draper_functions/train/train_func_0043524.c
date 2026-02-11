bUuEncode (const_bstring src) {
bstring out;
int i, j, jm;
unsigned int c0, c1, c2;
	if (src == NULL || src->slen < 0 || src->data == NULL) return NULL;
	if ((out = bfromcstr ("")) == NULL) return NULL;
	for (i=0; i < src->slen; i += UU_MAX_LINELEN) {
		if ((jm = i + UU_MAX_LINELEN) > src->slen) jm = src->slen;
		if (bconchar (out, UU_ENCODE_BYTE (jm - i)) < 0) {
			bstrFree (out);
			break;
		}
		for (j = i; j < jm; j += 3) {
			c0 = (unsigned int) bchar (src, j    );
			c1 = (unsigned int) bchar (src, j + 1);
			c2 = (unsigned int) bchar (src, j + 2);
			if (bconchar (out, UU_ENCODE_BYTE ( (c0 & 0xFC) >> 2)) < 0 ||
			    bconchar (out, UU_ENCODE_BYTE (((c0 & 0x03) << 4) | ((c1 & 0xF0) >> 4))) < 0 ||
			    bconchar (out, UU_ENCODE_BYTE (((c1 & 0x0F) << 2) | ((c2 & 0xC0) >> 6))) < 0 ||
			    bconchar (out, UU_ENCODE_BYTE ( (c2 & 0x3F))) < 0) {
				bstrFree (out);
				goto End;
			}
		}
		if (bconchar (out, (char) '\r') < 0 || bconchar (out, (char) '\n') < 0) {
			bstrFree (out);
			break;
		}
	}
	End:;
	return out;
}
