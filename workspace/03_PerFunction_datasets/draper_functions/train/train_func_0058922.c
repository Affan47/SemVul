checkAndRemovePages(void)
{
	UT_GenericVector <fl_HdrFtrSectionLayout *> vecHdrFtr;
	getVecOfHdrFtrs( &vecHdrFtr);
	UT_sint32 i = 0;
	for(i = 0; i < vecHdrFtr.getItemCount(); i++)
	{
		fl_HdrFtrSectionLayout * pHdrFtr = vecHdrFtr.getNthItem(i);
		pHdrFtr->checkAndRemovePages();
	}
}
