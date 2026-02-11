getCellFormat(PT_DocPosition pos, UT_String & sCellProps) const
{
	sCellProps.clear();
	if(!isInTable(pos))
	{
		return false;
	}
	const PP_AttrProp * pCellAP = NULL;
	fl_BlockLayout * pBL =  _findBlockAtPosition(pos);
	if(!pBL)
	{
		UT_ASSERT(UT_SHOULD_NOT_HAPPEN);
		return false;
	}
	fl_SectionLayout * pCell = static_cast<fl_CellLayout *>(pBL->myContainingLayout());
	if(!pCell)
	{
		UT_ASSERT(UT_SHOULD_NOT_HAPPEN);
		return false;
	}
	pCell->getAP(pCellAP);

	UT_sint32 iPropsCount = PP_getPropertyCount();
	UT_sint32 n = 0;
	UT_String sPropName;
	UT_String sPropVal;
	const gchar * pszPropVal;
	for(n = 0; n < iPropsCount; n++)
	{
		if((PP_getNthPropertyLevel(n) & PP_LEVEL_TABLE))
		{
			sPropName = PP_getNthPropertyName(n);
			sPropVal.clear();
			bool bFound = pCellAP->getProperty(sPropName.c_str(),pszPropVal);
			if(bFound)
			{
				sPropVal = pszPropVal;
				UT_String_setProperty(sCellProps,sPropName,sPropVal);
			}
		}
	}
	return true;
}
