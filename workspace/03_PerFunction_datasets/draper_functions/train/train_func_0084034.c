GenerateFsmMachineClasses(GrcManager * pcman)
{
	if (m_nGlobalID == -1)
		return;

	InitializeFsmArrays();


	std::vector<GdlGlyphClassDefn *> * pvpglfcThisPass = pcman->FsmClassesForPass(m_nGlobalID);


	for (size_t i = 0; i < pvpglfcThisPass->size(); i++)
		(*pvpglfcThisPass)[i]->RecordInclusionInClass(this);


	for (utf16 w = 0; w < kMaxTotalGlyphs; w++)
	{
		int ifsmcColumn = AssignGlyphIDToMachineClasses(w, m_nGlobalID);
		if (ifsmcColumn > -1)
		{
			std::pair<utf16, utf16> hmPair;
			hmPair.first = w;
			hmPair.second = ifsmcColumn;
			m_hmGlyphToColumn.insert(hmPair);

		}
	}


	if (m_critMaxPreContext > m_critMinPreContext)
	{


		Symbol psymAnyClass = pcman->SymbolTable()->FindSymbol("ANY");
		GdlGlyphClassDefn * pglfc = psymAnyClass->GlyphClassDefnData();
		Assert(pglfc);
		bool fFound = false;
		for (size_t ifsmc = 0; ifsmc < m_vpfsmc.size(); ifsmc++)
		{
			if (m_vpfsmc[ifsmc]->MatchesOneSource(pglfc))
			{
				fFound = true;
				break;
			}
		}


		Assert(fFound);


	}
}
