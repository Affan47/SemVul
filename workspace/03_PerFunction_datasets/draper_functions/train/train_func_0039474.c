GetFolderFromPath(const fstring& folder, fstring& path)
{
	path = StripFileFromPath(folder);
	if (path.length() > 0 && (path.back() == UNWANTED_FOLDER_CHAR || path.back() == FOLDER_CHAR))
	{
		path.pop_back();
	}
}
