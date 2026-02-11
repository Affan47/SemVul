StorePseudoToActualAsGlyphAttr(GrcGlyphAttrMatrix * pgax, int nAttrID,
	std::vector<GdlExpression *> & vpexpExtra)
{
	if (m_glft == kglftPseudo && m_pglfOutput && m_pglfOutput->m_vwGlyphIDs.size() > 0)
	{
		utf16 wOutput = m_pglfOutput->m_vwGlyphIDs[0];
		GdlExpression * pexp = new GdlNumericExpression(wOutput);
		vpexpExtra.push_back(pexp);
		pgax->Set(m_wPseudo, nAttrID, pexp, 0, 0, true, false, GrpLineAndFile(0, 0, ""));
	}
}
