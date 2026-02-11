clean_hash(void)

{
	int i;
	for (i = 0; i < 4096; i++) {
		Node *p = table[i];
		table[i] = NULL;
		while (p) {
			Node *q = p->hash_next;
			free(p);
			p = q;
		}
	}
	entries = 0;
	head_node = NULL;
}
