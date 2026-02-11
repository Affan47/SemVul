testDiffItem(MathAtom const & at)
{
	if (testString(at, "d") || testSymbol(at, "partial"))
		return true;


	InsetMathScript const * sup = at->asScriptInset();
	if (sup && !sup->hasDown() && sup->hasUp() && sup->nuc().size() == 1) {
		MathAtom const & ma = sup->nuc().front();
		return testString(ma, "d") || testSymbol(ma, "partial");
	}
	return false;
}
