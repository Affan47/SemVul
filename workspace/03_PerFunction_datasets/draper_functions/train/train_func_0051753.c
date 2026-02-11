bJustifyLeft (bstring b, int space) {
int j, i, s, t;
unsigned char c = (unsigned char) space;

	if (b == NULL || b->slen < 0 || b->mlen < b->slen) return -__LINE__;
	if (space != (int) c) return BSTR_OK;

	for (s=j=i=0; i < b->slen; i++) {
		t = s;
		s = c != (b->data[j] = b->data[i]);
		j += (t|s);
	}
	if (j > 0 && b->data[j-1] == c) j--;

	b->data[j] = (unsigned char) '\0';
	b->slen = j;
	return BSTR_OK;
}
