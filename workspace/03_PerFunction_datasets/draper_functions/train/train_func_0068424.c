bsplitstr (const_bstring str, const_bstring splitStr) {
struct genBstrList g;

	if (str == NULL || str->data == NULL || str->slen < 0) return NULL;

	g.bl = (struct bstrList *) bstr__alloc (sizeof (struct bstrList));
	if (g.bl == NULL) return NULL;
	g.bl->mlen = 4;
	g.bl->entry = (bstring *) bstr__alloc (g.bl->mlen * sizeof (bstring));
	if (NULL == g.bl->entry) {
		bstr__free (g.bl);
		return NULL;
	}

	g.b = (bstring) str;
	g.bl->qty = 0;
	if (bsplitstrcb (str, splitStr, 0, bscb, &g) < 0) {
		bstrListDestroy (g.bl);
		return NULL;
	}
	return g.bl;
}
