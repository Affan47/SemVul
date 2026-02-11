calculateValue(void)
{
	UT_UTF8String szFieldValue ("?");

	if (getLine() && getLine()->getContainer() && getLine()->getContainer()->getPage())
	{
		fp_Page* pPage = getLine()->getContainer()->getPage();
		pPage->resetFieldPageNumber();
		UT_sint32 iPageNum = pPage->getFieldPageNumber();
		if (iPageNum > 0)
		{
			UT_UTF8String_sprintf(szFieldValue, "%d", iPageNum);
		}
	}

	if (getField())
	  getField()->setValue(static_cast<const gchar*>(szFieldValue.utf8_str()));

	return _setValue(szFieldValue.ucs4_str().ucs4_str());
}
