AssignGlyphAttrsToClassMembers(GrcGlyphAttrMatrix * pgax,
	GdlRenderer * prndr, GrcLigComponentList * plclist,
	std::vector<GdlGlyphAttrSetting *> & vpglfaAttrs, int cgid, int & igid)
{
	for (size_t iglfd = 0; iglfd < m_vpglfdMembers.size(); iglfd++)
	{
		m_vpglfdMembers[iglfd]->AssignGlyphAttrsToClassMembers(pgax, prndr, plclist,
			vpglfaAttrs, cgid, igid);
	}
}
