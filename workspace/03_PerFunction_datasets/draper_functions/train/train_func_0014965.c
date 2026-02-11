coalesceHistory(const PX_ChangeRecord * pcr)
{


	UT_sint32 iAdj = m_iAdjustOffset;
	PX_ChangeRecord * pcrUndo = m_vecChangeRecords.getNthItem(m_undoPosition-1);
	UT_return_if_fail (pcrUndo);
	UT_return_if_fail (pcr->getType() == pcrUndo->getType());

	switch (pcr->getType())
	{
		case PX_ChangeRecord::PXT_InsertSpan:
		case PX_ChangeRecord::PXT_DeleteSpan:
			{
				const PX_ChangeRecord_Span * pcrSpan = static_cast<const PX_ChangeRecord_Span *>(pcr);
				PX_ChangeRecord_Span * pcrSpanUndo = static_cast<PX_ChangeRecord_Span *>(pcrUndo);

				if(pcr->isFromThisDoc())
				{
				  _invalidateRedo();
				  m_iAdjustOffset = 0;
				}
				else if(iAdj > 0)
				{
				    m_iAdjustOffset = iAdj - 1;
				    xxx_UT_DEBUGMSG(("AdjustOffset decremented - 3 %d ", m_iAdjustOffset));

				}
				pcrSpanUndo->coalesce(pcrSpan);
			}
			return;

		default:
			UT_ASSERT_HARMLESS(0);
			return;
	}
}
