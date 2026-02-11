initialize()
{
	mFile = fopen(mFileName.c_str(), "r");
	if (mFile==NULL)
	{
		outDebug(4, std::cout << "file not found:" << mFileName << std::endl);
		openTemplate();
	}
	buildConfig(ConfigFile::File);
	if (mFile != NULL)
	{
		fclose(mFile);
		mFile = NULL;
	}
}
