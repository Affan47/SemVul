testEncryptedZip(IFileSystem* fs)
{

	if ( fs->getFileArchiveCount() )
	{
		logTestString("Already mounted archives found\n");
		return false;
	}

	const char* archiveName = "media/enc.zip";
	if ( !fs->addFileArchive(archiveName, true, false) )
	{
		logTestString("Mounting archive failed\n");
		return false;
	}


	if ( !fs->getFileArchiveCount() )
	{
		logTestString("Mounted archive not in list\n");
		return false;
	}


	if ( !fs->addFileArchive(archiveName, true, false) )
	{
		logTestString("Mounting a second time failed\n");
		return false;
	}


	if ( fs->getFileArchiveCount() != 1 )
	{
		logTestString("Duplicate mount not recognized\n");
		return false;
	}


	io::IFileArchive* archive = fs->getFileArchive(fs->getFileArchiveCount()-1);
	const io::IFileList* fileList = archive->getFileList();
	for ( u32 f=0; f < fileList->getFileCount(); ++f)
	{
		logTestString("File name: %s\n", fileList->getFileName(f).c_str());
		logTestString("Full path: %s\n", fileList->getFullFileName(f).c_str());
	}

	io::path filename("doc/readme.txt");
	if (!fs->existFile(filename))
	{
		logTestString("existFile failed\n");
		return false;
	}

	IReadFile* readFile = fs->createAndOpenFile(filename);
	if ( readFile )
	{
		logTestString("createAndOpenFile succeeded, even though no password was set.\n");
		return false;
	}

	archive->Password="33445";
	readFile = fs->createAndOpenFile(filename);
#ifdef _IRR_COMPILE_WITH_ZIP_ENCRYPTION_
	if ( !readFile )
	{
		logTestString("createAndOpenFile failed\n");
		return false;
	}

	char tmp[13] = {'\0'};
	readFile->read(tmp, 12);
	if (strncmp(tmp, "Linux Users:", 12))
	{
		logTestString("Read bad data from archive: %s\n", tmp);
		return false;
	}
#endif

	if (!fs->removeFileArchive(fs->getFileArchiveCount()-1))
	{
		logTestString("Couldn't remove archive.\n");
		return false;
	}


	if ( fs->getFileArchiveCount() )
		return false;

	return true;
}
