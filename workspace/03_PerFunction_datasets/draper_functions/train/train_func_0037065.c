bitmap_convolve(struct bitmap *a, struct bitmap *b, int (*f) (int x))
{
	int L = a->width * a->height;
	int i;
	for(i = 0; i < L; i++) {
		b->data[i] = f(a->data[i]);
	}
}
