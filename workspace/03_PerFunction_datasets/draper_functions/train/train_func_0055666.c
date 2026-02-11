changeLastStruxFmtNoUndo(PT_DocPosition dpos, PTStruxType pts,
										   const gchar ** attributes, const gchar * props,
									 bool bSkipEmbededSections)
{
	UT_return_val_if_fail (m_pPieceTable, false);

	return m_pPieceTable->changeLastStruxFmtNoUndo(dpos, pts,attributes,props,bSkipEmbededSections);
}
