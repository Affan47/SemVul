make(const Node& n, int ar, Tree* tbl)
{
	tvec	br(ar);

	for (int i=0; i<ar; i++)  br[i] = tbl[i];

	unsigned int 	hk  = calcTreeHash(n, br);
	Tree	t = gHashTable[hk % kHashTableSize];

	while (t && !t->equiv(n, br)) {
		t = t->fNext;
	}
	return (t) ? t : new CTree(hk, n, br);
}
