_importFile(const char * szFilename, int ieft,
								  bool markClean, bool bImportStylesFirst,
								  bool bIsImportFile, const char* impProps)
{
	GsfInput * input;

	input = UT_go_file_open(szFilename, NULL);
	if (!input)
	{
		UT_DEBUGMSG(("PD_Document::importFile -- invalid filename\n"));
		return UT_INVALIDFILENAME;
	}

	UT_Error result = _importFile(input, ieft, markClean, bImportStylesFirst, bIsImportFile, impProps);

	g_object_unref (G_OBJECT (input));

	return result;
}
