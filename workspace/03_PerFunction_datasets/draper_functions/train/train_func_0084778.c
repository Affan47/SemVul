_deleteComplexSpan_norec(PT_DocPosition dpos1,
											 PT_DocPosition dpos2)
{
	pf_Frag * pfNewEnd;
	UT_uint32 fragOffsetNewEnd;

	pf_Frag * pf_First;
	pf_Frag * pf_End;
	PT_BlockOffset fragOffset_First;
	PT_BlockOffset fragOffset_End;

	bool bFound = getFragsFromPositions(dpos1,dpos2,&pf_First,&fragOffset_First,&pf_End,&fragOffset_End);
	UT_return_val_if_fail (bFound, false);

	pf_Frag_Strux * pfsContainer = NULL;
	bool bFoundStrux = _getStruxFromPosition(dpos1,&pfsContainer);
	UT_return_val_if_fail (bFoundStrux, false);


	UT_uint32 length = dpos2 - dpos1;
	while (length > 0)
	{
		UT_uint32 lengthInFrag = pf_First->getLength() - fragOffset_First;
		UT_uint32 lengthThisStep = UT_MIN(lengthInFrag, length);

		switch (pf_First->getType())
		{
		case pf_Frag::PFT_EndOfDoc:
		default:
			UT_ASSERT_HARMLESS(0);
			return false;

		case pf_Frag::PFT_Strux:
		{
			pf_Frag_Strux * pfs = static_cast<pf_Frag_Strux *> (pf_First);

			bool bResult = _deleteStruxWithNotify(dpos1,pfs,
									   &pfNewEnd,&fragOffsetNewEnd,
									   false);
			UT_return_val_if_fail (bResult, false);

		}
		break;

		case pf_Frag::PFT_Text:
		{
			bool bResult = _deleteSpanWithNotify(dpos1,
									  static_cast<pf_Frag_Text *>(pf_First),
									  fragOffset_First,lengthThisStep,
									  pfsContainer,&pfNewEnd,
									  &fragOffsetNewEnd, false);
			UT_return_val_if_fail (bResult, false);
		}
		break;

		case pf_Frag::PFT_Object:
		{
			bool bResult = _deleteObjectWithNotify(dpos1,static_cast<pf_Frag_Object *>(pf_First),
									fragOffset_First,lengthThisStep,
									pfsContainer,&pfNewEnd,&fragOffsetNewEnd,
									false);
			UT_return_val_if_fail (bResult, false);
		}
		break;

		case pf_Frag::PFT_FmtMark:

			UT_ASSERT_HARMLESS(UT_SHOULD_NOT_HAPPEN);
			break;

		}


		length -= lengthThisStep;


		pf_First = pfNewEnd;
		if (!pf_First)
			length = 0;
		fragOffset_First = fragOffsetNewEnd;
	}

	return true;
}
