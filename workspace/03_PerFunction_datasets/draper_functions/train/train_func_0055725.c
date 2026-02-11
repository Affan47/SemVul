mk_followpos(tree, npos)
Re_node tree;
int npos;
{
	int i;
	Pset_array fpos;

	if (tree == NULL || npos < 0) return NULL;
	fpos = (Pset_array) malloc((unsigned) (npos+1)*sizeof(Pset));
	if (fpos == NULL) return NULL;
	for (i = 0; i <= npos; i++) (*fpos)[i] = NULL;
	mk_followpos_1(tree, fpos);
	return fpos;
}
