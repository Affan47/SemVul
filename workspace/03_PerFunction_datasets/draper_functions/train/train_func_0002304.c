GetRuleTable(GrpLineAndFile & lnf, std::string staTableName)
{
	GdlRuleTable * prultbl = FindRuleTable(staTableName);

	if (prultbl)
		return prultbl;


	Symbol psymTableName = g_cman.SymbolTable()->FindSymbol(staTableName);
	Assert(psymTableName);
	if (!psymTableName || !psymTableName->FitsSymbolType(ksymtTableRule))
	{
		g_errorList.AddError(2162, NULL,
			"The ",
			staTableName,
			" table cannot hold rules",
			lnf);
		return NULL;
	}

	prultbl = new GdlRuleTable(psymTableName);
	prultbl->SetLineAndFile(lnf);
	m_vprultbl.push_back(prultbl);

	return prultbl;
}
