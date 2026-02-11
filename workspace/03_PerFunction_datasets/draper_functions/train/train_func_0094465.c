getCount(Tree t)
{
	Tree c;
	return (getProperty(t, fKey, c)) ? c->node().getInt() : 0;
}
