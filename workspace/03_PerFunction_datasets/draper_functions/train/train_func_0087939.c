ReadTable(TableId ktiTableId, void * pHdr, void * pTableDir,
	gr::byte ** ppTable, long * plnSize)
{
	size_t lnOffset, lnSize;

	if (!TtfUtil::GetTableInfo(ktiTableId, pHdr, pTableDir, lnOffset, lnSize))
		goto error;
	if (!ReadData(ppTable, lnOffset, lnSize))
		goto error;
	*plnSize = lnSize;
	if (!TtfUtil::CheckTable(ktiTableId, *ppTable, lnSize))
		goto error;

	return true;

error:
	if (*ppTable)
		delete [] *ppTable;
	*ppTable = NULL;
	*plnSize = 0;
	long lnTableTag = TtfUtil::TableIdTag(ktiTableId);
	char chTableTag[5];
	strncpy(chTableTag, (char *)&lnTableTag, 4);
	chTableTag[4] = '\0';

	if (!lnTableTag)
	{
		g_errorList.AddError(128, NULL,
			"Error reading table: ",
			chTableTag);
	}

	return false;
}
