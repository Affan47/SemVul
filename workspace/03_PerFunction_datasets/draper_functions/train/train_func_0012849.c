getMesh(io::IReadFile* file)
{
	if (!file)
		return 0;

	io::path name = file->getFileName();
	IAnimatedMesh* msh = MeshCache->getMeshByName(file->getFileName());
	if (msh)
		return msh;

	s32 count = MeshLoaderList.size();
	for (s32 i=count-1; i>=0; --i)
	{
		if (MeshLoaderList[i]->isALoadableFileExtension(name))
		{

			file->seek(0);
			msh = MeshLoaderList[i]->createMesh(file);
			if (msh)
			{
				MeshCache->addMesh(file->getFileName(), msh);
				msh->drop();
				break;
			}
		}
	}

	if (!msh)
		os::Printer::log("Could not load mesh, file format seems to be unsupported", file->getFileName(), ELL_ERROR);
	else
		os::Printer::log("Loaded mesh", file->getFileName(), ELL_INFORMATION);

	return msh;
}
