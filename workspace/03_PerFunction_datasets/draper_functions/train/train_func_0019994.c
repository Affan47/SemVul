pqdownheap(ct_data * tree, int k)
{
	int v = G2.heap[k];
	int j = k << 1;

	while (j <= G2.heap_len) {

		if (j < G2.heap_len && SMALLER(tree, G2.heap[j + 1], G2.heap[j]))
			j++;


		if (SMALLER(tree, v, G2.heap[j]))
			break;


		G2.heap[k] = G2.heap[j];
		k = j;


		j <<= 1;
	}
	G2.heap[k] = v;
}
