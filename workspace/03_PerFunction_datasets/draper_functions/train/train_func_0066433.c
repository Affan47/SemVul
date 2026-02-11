appendLastStruxFmt(PTStruxType pts, const gchar ** attributes, const gchar ** props,
									 bool bSkipEmbededSections)
{
	UT_return_val_if_fail (m_pPieceTable, false);
	updateStatus();
	return m_pPieceTable->appendLastStruxFmt(pts,attributes,props,bSkipEmbededSections);
}
