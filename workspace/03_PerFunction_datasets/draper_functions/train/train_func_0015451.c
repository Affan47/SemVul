analysergetsymbolcount(Symbol *l, int *c)
{
	if (l) {
		analysergetsymbolcount(l->left, c);
		if (l->location) (*c)++;
		analysergetsymbolcount(l->right, c);
	}
}
