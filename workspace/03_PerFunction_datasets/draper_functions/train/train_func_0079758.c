ClassPredefGlyphAttr(std::vector<std::string> & vsta,
	ExpressionType * pexpt, SymbolType * psymt)
{
	std::string sta1 = vsta[0];
	Symbol psymClass = SymbolTable()->FindSymbol(sta1);
	if (!psymClass || !psymClass->FitsSymbolType(ksymtClass))
		return false;

	std::vector<std::string> vstaMinusClass;
	for (size_t ista = 1; ista < vsta.size(); ista++)
		vstaMinusClass.push_back(vsta[ista]);
	Symbol psymGlyphAttr = SymbolTable()->FindSymbol(GrcStructName(vstaMinusClass));
	if (!psymGlyphAttr)
		return false;

	if (psymGlyphAttr->FitsSymbolType(ksymtGlyphAttr) && !psymGlyphAttr->IsUserDefined())
	{
		*pexpt = psymGlyphAttr->ExpType();
		*psymt = ksymtGlyphAttr;
		return true;
	}
	else if (psymGlyphAttr->FitsSymbolType(ksymtGlyphMetric))
	{
		*pexpt = psymGlyphAttr->ExpType();
		*psymt = ksymtGlyphMetric;
		return true;
	}

	return false;
}
