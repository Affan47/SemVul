containsFootnoteReference(void)
{
	fp_Run * pRun = NULL;
	UT_sint32 i =0;
	bool bFound = false;
	for(i=0; (i< countRuns()) && !bFound; i++)
	{
		pRun = getRunFromIndex(static_cast<UT_uint32>(i));
		if(pRun->getType() == FPRUN_FIELD)
		{
			fp_FieldRun * pFRun = static_cast<fp_FieldRun *>(pRun);
			if(pFRun->getFieldType() == FPFIELD_footnote_ref)
			{
				bFound = true;
				break;
			}
		}
	}
	return bFound;
}
