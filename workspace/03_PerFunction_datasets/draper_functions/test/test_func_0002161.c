CheckRulesForErrors(GrcGlyphAttrMatrix * pgax, GrcFont * pfont,
	GdlRenderer * prndr, GdlRule * prule, Symbol psymTable,
	int grfrco, int irit, bool fAnyAssocs,
	std::vector<bool> & vfLb, std::vector<bool> & vfIns, std::vector<bool> & vfDel,
	std::vector<int> & vcwSizes)
{
	bool fOkay = true;

	if ((grfrco & kfrcoLb) == 0)
	{
		g_errorList.AddError(3108, this,
			"Line-break inappropriate in ",
			psymTable->FullName(),
			" table");
		fOkay = false;
	}


	if(!GdlRuleItem::CheckRulesForErrors(pgax, pfont, prndr, prule, psymTable,
		grfrco, irit, fAnyAssocs, vfLb, vfIns, vfDel, vcwSizes))
	{
		fOkay = false;
	}

	return fOkay;
}
