bdelta_init_alg(unsigned data1_size, unsigned data2_size,
		bdelta_readCallback cb, void *handle1, void *handle2,
		unsigned tokenSize) {
	if (tokenSize != sizeof(Token)) {
		printf("Error: BDelta library compiled for token size of %lu.\n", sizeof(Token));
		return 0;
	}
	BDelta_Instance *b = new BDelta_Instance;
	if (!b) return 0;
	b->data1_size = data1_size;
	b->data2_size = data2_size;
	b->cb = cb;
	b->handle1 = handle1;
	b->handle2 = handle2;
	b->access_int = -1;
	return b;
}
