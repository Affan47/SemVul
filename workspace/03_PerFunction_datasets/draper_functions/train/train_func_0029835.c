fh_insertkey(struct fibheap *h, int key, void *data)
{
	struct fibheap_el *x;

	if ((x = fhe_newelem()) == NULL)
		return NULL;


	x->fhe_data = data;
	x->fhe_key = key;

	fh_insertel(h, x);

	return x;
}
