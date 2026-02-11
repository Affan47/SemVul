AddSymbolAux(const GrcStructName & xns,
	SymbolType symtLeaf, SymbolType symtOther, GrpLineAndFile const& lnf)
{
	Symbol psym = NULL;
	GrcSymbolTable * psymtbl = this;

	for (int i = 0; i < xns.NumFields(); ++i)
	{
		std::string staField = xns.FieldAt(i);

		if (psymtbl == NULL)
		{
			psymtbl = new GrcSymbolTable(false);
			psymtbl->MakeSubTableOf(psym);
		}

		psym = psymtbl->FindField(staField);
		if (psym == NULL)
		{
			psym = new GrcSymbolTableEntry(staField,
				((i == xns.NumFields() - 1) ? symtLeaf : symtOther),
				psymtbl);
			SymbolTablePair hmpair;
			hmpair.first = staField;
			hmpair.second = psym;
			psymtbl->m_hmstasymEntries.insert(hmpair);

		}
		psymtbl = psym->m_psymtblSubTable;
	}


	if (psym->m_lnf.NotSet())
		psym->m_lnf = lnf;

	if (psym->m_symt == ksymtInvalid)
		psym->SetSymbolType(symtLeaf);

	Assert(psym->m_symt == symtLeaf);

	return psym;
}
