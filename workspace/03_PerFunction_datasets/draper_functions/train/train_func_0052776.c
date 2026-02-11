_invalidateRedo(void)
{
	UT_sint32 kLimit = m_vecChangeRecords.getItemCount();
	UT_return_if_fail (m_undoPosition <= kLimit);

	UT_sint32 i = m_undoPosition - m_iAdjustOffset;
	for (UT_sint32 k = m_undoPosition - m_iAdjustOffset; k < kLimit; k++)
	{
		PX_ChangeRecord * pcrTemp = m_vecChangeRecords.getNthItem(i);
		if (!pcrTemp)
			break;
		if (pcrTemp->isFromThisDoc())
		{
		    delete pcrTemp;
		    m_vecChangeRecords.deleteNthItem(i);
		}
		else
		    i++;
	}
	m_undoPosition = m_vecChangeRecords.getItemCount();
	if (m_savePosition > m_undoPosition)
		m_savePosition = -1;
	m_iAdjustOffset = 0;
}
