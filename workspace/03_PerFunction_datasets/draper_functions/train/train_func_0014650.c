ModPlug_Unload(ModPlugFile* file)
{
	file->mSoundFile.Destroy();
	delete file;
}
