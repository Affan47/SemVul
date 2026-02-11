renameFile(const std::string& zipPath, const std::string& newZipPath)
{
	const ZipLocalFileHeader& entry = getForChange(zipPath);

	std::string fn = ZipUtil::validZipEntryFileName(newZipPath);
	addOperation(zipPath, new Rename(entry, fn));
}
