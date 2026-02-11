existFile(const io::path& filename) const
{
	for (u32 i=0; i < FileArchives.size(); ++i)
		if (FileArchives[i]->getFileList()->findFile(filename)!=-1)
			return true;

#if defined(_IRR_WINDOWS_CE_PLATFORM_)
#if defined(_IRR_WCHAR_FILESYSTEM)
	HANDLE hFile = CreateFileW(filename.c_str(), GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);
#else
	HANDLE hFile = CreateFileW(core::stringw(filename).c_str(), GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);
#endif
	if (hFile == INVALID_HANDLE_VALUE)
		return false;
	else
	{
		CloseHandle(hFile);
		return true;
	}
#else
	_IRR_IMPLEMENT_MANAGED_MARSHALLING_BUGFIX;
#if defined(_MSC_VER)
#if defined(_IRR_WCHAR_FILESYSTEM)
	return (_waccess(filename.c_str(), 0) != -1);
#else
	return (_access(filename.c_str(), 0) != -1);
#endif
#elif defined(F_OK)
	return (access(filename.c_str(), F_OK) != -1);
#else
    return (access(filename.c_str(), 0) != -1);
#endif
#endif
}
