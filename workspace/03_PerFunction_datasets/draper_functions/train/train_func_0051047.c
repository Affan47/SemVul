UnpackArchive(const CPath& path, const wxChar* files[])
{
	const wxString file = path.GetRaw();


	EFileType type = GuessFiletype(file);
	switch (type) {
		case EFT_Zip:
			if (UnpackZipFile(file, files)) {

				return UnpackResult(true, UnpackArchive(path, files).second);
			} else {
				return UnpackResult(false, EFT_Error);
			}

		case EFT_GZip:
			if (UnpackGZipFile(file)) {

				return UnpackResult(true, UnpackArchive(path, files).second);
			} else {
				return UnpackResult(false, EFT_Error);
			}

		default:
			return UnpackResult(false, type);
	}
}
