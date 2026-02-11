changeStruxFmt(PTChangeFmt ptc,
								 PT_DocPosition dpos1,
								 PT_DocPosition dpos2,
								 const gchar ** attributes,
								 const gchar ** properties)
{
	if(isDoingTheDo())
	{
		return false;
	}
	return m_pPieceTable->changeStruxFmt(ptc,dpos1,dpos2,attributes,properties);
}
