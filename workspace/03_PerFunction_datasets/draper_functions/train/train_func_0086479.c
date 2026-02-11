startree_compute_inverse_perm(startree_t* s) {
	if (s->inverse_perm)
		return;

	s->inverse_perm = malloc(Ndata(s) * sizeof(int));
	if (!s->inverse_perm) {
		fprintf(stderr, "Failed to allocate star kdtree inverse permutation vector.\n");
		return;
	}
#ifndef NDEBUG
	{
		int i;
		for (i=0; i<Ndata(s); i++)
			s->inverse_perm[i] = -1;
	}
#endif
	kdtree_inverse_permutation(s->tree, s->inverse_perm);
#ifndef NDEBUG
	{
		int i;
		for (i=0; i<Ndata(s); i++)
			assert(s->inverse_perm[i] != -1);
	}
#endif
}
