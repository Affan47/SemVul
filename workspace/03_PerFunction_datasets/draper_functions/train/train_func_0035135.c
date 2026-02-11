PropagateLineAndFile(GrpLineAndFile & lnf)
{
	if (LineIsZero())
	{
		SetLineAndFile(lnf);
		if (m_pexpSelector)
			m_pexpSelector->PropagateLineAndFile(lnf);
	}
}
