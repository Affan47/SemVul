liftn(Tree t, int threshold)
{
	Tree L 	= tree( Node(SYMLIFTN), tree(Node(threshold)) );
	Tree t2 = t->getProperty(L);

	if (!t2) {
		t2 = calcliftn(t, threshold);
		t->setProperty(L, t2);
	}
	return t2;

}
