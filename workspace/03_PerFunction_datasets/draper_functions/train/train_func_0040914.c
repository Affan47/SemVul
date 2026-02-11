fileClose (void)
{
	if (File.fp != NULL)
	{


		if (Option.printTotals)
		{
			fileStatus *status = eStat (vStringValue (File.name));
			addTotals (0, File.lineNumber - 1L, status->size);
		}
		fclose (File.fp);
		File.fp = NULL;
	}
}
