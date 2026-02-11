CFileSystem()
{
	#ifdef _DEBUG
	setDebugName("CFileSystem");
	#endif

	setFileListSystem(FILESYSTEM_NATIVE);

	getWorkingDirectory();

#ifdef __IRR_COMPILE_WITH_ZIP_ARCHIVE_LOADER_
	ArchiveLoader.push_back(new CArchiveLoaderZIP(this));
#endif

#ifdef __IRR_COMPILE_WITH_MOUNT_ARCHIVE_LOADER_
	ArchiveLoader.push_back(new CArchiveLoaderMount(this));
#endif

#ifdef __IRR_COMPILE_WITH_PAK_ARCHIVE_LOADER_
	ArchiveLoader.push_back(new CArchiveLoaderPAK(this));
#endif

#ifdef __IRR_COMPILE_WITH_NPK_ARCHIVE_LOADER_
	ArchiveLoader.push_back(new CArchiveLoaderNPK(this));
#endif

#ifdef __IRR_COMPILE_WITH_TAR_ARCHIVE_LOADER_
	ArchiveLoader.push_back(new CArchiveLoaderTAR(this));
#endif
}
