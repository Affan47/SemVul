breplace (bstring b1, int pos, int len, const_bstring b2,
			  unsigned char fill) {
int pl, ret;
ptrdiff_t pd;
bstring aux = (bstring) b2;

	if (pos < 0 || len < 0 || (pl = pos + len) < 0 || b1 == NULL ||
	    b2 == NULL || b1->data == NULL || b2->data == NULL ||
	    b1->slen < 0 || b2->slen < 0 || b1->mlen < b1->slen ||
	    b1->mlen <= 0) return BSTR_ERR;


	if (pl >= b1->slen) {
		if ((ret = bsetstr (b1, pos, b2, fill)) < 0) return ret;
		if (pos + b2->slen < b1->slen) {
			b1->slen = pos + b2->slen;
			b1->data[b1->slen] = (unsigned char) '\0';
		}
		return ret;
	}


	if ((pd = (ptrdiff_t) (b2->data - b1->data)) >= 0 && pd < (ptrdiff_t) b1->slen) {
		if (NULL == (aux = bstrcpy (b2))) return BSTR_ERR;
	}

	if (aux->slen > len) {
		if (balloc (b1, b1->slen + aux->slen - len) != BSTR_OK) {
			if (aux != b2) bdestroy (aux);
			return BSTR_ERR;
		}
	}

	if (aux->slen != len) bstr__memmove (b1->data + pos + aux->slen, b1->data + pos + len, b1->slen - (pos + len));
	bstr__memcpy (b1->data + pos, aux->data, aux->slen);
	b1->slen += aux->slen - len;
	b1->data[b1->slen] = (unsigned char) '\0';
	if (aux != b2) bdestroy (aux);
	return BSTR_OK;
}
