isBoxIdent(Tree t0, const char** str)
{
	Tree t1; Sym s;
	if ( isTree(t0, BOXIDENT, t1) && isSym(t1->node(), &s) ) {
		*str = name(s);
		return true;
	} else {
		return false;
	}
}
