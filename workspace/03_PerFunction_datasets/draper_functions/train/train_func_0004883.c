tgt_create(int numleafsh, int numleafsv) {
	int nplh[32];
	int nplv[32];
	opj_tgt_node_t *node = NULL;
	opj_tgt_node_t *parentnode = NULL;
	opj_tgt_node_t *parentnode0 = NULL;
	opj_tgt_tree_t *tree = NULL;
	int i, j, k;
	int numlvls;
	int n;

	tree = (opj_tgt_tree_t *) opj_malloc(sizeof(opj_tgt_tree_t));
	if(!tree) return NULL;
	tree->numleafsh = numleafsh;
	tree->numleafsv = numleafsv;

	numlvls = 0;
	nplh[0] = numleafsh;
	nplv[0] = numleafsv;
	tree->numnodes = 0;
	do {
		n = nplh[numlvls] * nplv[numlvls];
		nplh[numlvls + 1] = (nplh[numlvls] + 1) / 2;
		nplv[numlvls + 1] = (nplv[numlvls] + 1) / 2;
		tree->numnodes += n;
		++numlvls;
	} while (n > 1);


	if (tree->numnodes == 0) {
		opj_free(tree);
		return NULL;
	}

	tree->nodes = (opj_tgt_node_t*) opj_calloc(tree->numnodes, sizeof(opj_tgt_node_t));
	if(!tree->nodes) {
		opj_free(tree);
		return NULL;
	}

	node = tree->nodes;
	parentnode = &tree->nodes[tree->numleafsh * tree->numleafsv];
	parentnode0 = parentnode;

	for (i = 0; i < numlvls - 1; ++i) {
		for (j = 0; j < nplv[i]; ++j) {
			k = nplh[i];
			while (--k >= 0) {
				node->parent = parentnode;
				++node;
				if (--k >= 0) {
					node->parent = parentnode;
					++node;
				}
				++parentnode;
			}
			if ((j & 1) || j == nplv[i] - 1) {
				parentnode0 = parentnode;
			} else {
				parentnode = parentnode0;
				parentnode0 += nplh[i];
			}
		}
	}
	node->parent = 0;

	tgt_reset(tree);

	return tree;
}
