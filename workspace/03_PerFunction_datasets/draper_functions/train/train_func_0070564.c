fix_keys (node_t *pn,void *okey,CMP)
{
	register int nix;
	register node_t *n=pn->parent;
	register void *nkey=pn->e[0].key;

	if (pn->nel==0)
		return;

	while (n != NULL) {
		nix=find_ix(n,okey,cmp,NULL);
		n->e[nix].key=nkey;
		if (nix != 0)
			n=NULL;
		else
			n=n->parent;
	}
}
