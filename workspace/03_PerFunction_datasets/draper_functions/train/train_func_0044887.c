parseFileOptions (const char* const fileName)
{
	boolean fileFound = FALSE;
	const char* const format = "Considering option file %s: %s\n";
	CheckFile = fileName;
	if (stringListHasTest (OptionFiles, checkSameFile))
		verbose (format, fileName, "already considered");
	else
	{
		FILE* const fp = fopen (fileName, "r");
		if (fp == NULL)
			verbose (format, fileName, "not found");
		else
		{
			cookedArgs* const args = cArgNewFromLineFile (fp);
			vString* file = vStringNewInit (fileName);
			stringListAdd (OptionFiles, file);
			verbose (format, fileName, "reading...");
			parseOptions (args);
			if (NonOptionEncountered)
				error (WARNING, "Ignoring non-option in %s\n", fileName);
			cArgDelete (args);
			fclose (fp);
			fileFound = TRUE;
		}
	}
	return fileFound;
}
