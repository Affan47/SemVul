addExternalFile(string const & format,
				 FileName const & sourceName)
{
	addExternalFile(format, sourceName, onlyFileName(sourceName.absFileName()));
}
