fh_replacekeydata(struct fibheap *h, struct fibheap_el *x, int key, void *data)
{
	void *odata;
	int okey;
	struct fibheap_el *y;
	int r;

	odata = x->fhe_data;
	okey = x->fhe_key;


	if ((r = fh_comparedata(h, key, data, x)) > 0) {

		abort();
		fh_deleteel(h, x);

		x->fhe_data = data;
		x->fhe_key = key;

		fh_insertel(h, x);

		return odata;
	}

	x->fhe_data = data;
	x->fhe_key = key;


	if (r == 0)
		return odata;

	y = x->fhe_p;

	if (h->fh_keys && okey == key)
		return odata;

	if (y != NULL && fh_compare(h, x, y) <= 0) {
		fh_cut(h, x, y);
		fh_cascading_cut(h, y);
	}


	if (fh_compare(h, x, h->fh_min) <= 0)
		h->fh_min = x;

	return odata;
}
