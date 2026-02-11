epimung(tree *comp, tree *epi)
{
	tree *p;
	if(epi==0)
		return comp;
	for(p = epi;p->child[1];p = p->child[1]);
	p->child[1] = comp;
	return epi;
}
