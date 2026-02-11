FixGlyphAttrsInRules(GrcManager * pcman, GrcFont * pfont)
{
	for (size_t iprule = 0; iprule < m_vprule.size(); iprule++)
	{
		m_vprule[iprule]->FixGlyphAttrsInRules(pcman, pfont);
	}


	FixFeatureTestsInPass(pfont);
}
