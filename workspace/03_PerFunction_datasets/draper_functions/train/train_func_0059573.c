binchrr (const_bstring b0, int pos, const_bstring b1) {
struct charField chrs;
	if (pos < 0 || b0 == NULL || b0->data == NULL || b1 == NULL ||
	    b0->slen < pos) return BSTR_ERR;
	if (pos == b0->slen) pos--;
	if (1 == b1->slen) return bstrrchrp (b0, b1->data[0], pos);
	if (0 > buildCharField (&chrs, b1)) return BSTR_ERR;
	return binchrrCF (b0->data, pos, &chrs);
}
