Expected(Node *p, Symbol *curSy) {
	BitArray *s = First(p);
	if (DelGraph(p))
		s->Or(curSy->follow);
	return s;
}
