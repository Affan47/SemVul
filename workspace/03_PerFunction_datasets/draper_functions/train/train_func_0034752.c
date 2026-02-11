rll_copy(rll_t *e, rllitr_t *itr, const rll_t *e0, rllitr_t *itr0, int64_t k)
{
	if (itr0->l >= k) {
		rll_enc(e, itr, k, itr0->c);
		itr0->l -= k;
	} else {
		int c = -1;
		int64_t l;
		rll_enc(e, itr, itr0->l, itr0->c);
		k -= itr0->l;
		for (; k > 0; k -= l) {
			l = rll_dec(e0, itr0, &c, 1);
			rll_enc(e, itr, k < l? k : l, c);
		}
		itr0->l = -k; itr0->c = c;
	}
}
