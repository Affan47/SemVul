createMesh(io::IReadFile* file)
{
	IAnimatedMesh* msh = new CAnimatedMeshMD2();
	if (msh)
	{
		if (loadFile(file, (CAnimatedMeshMD2*)msh) )
			return msh;

		msh->drop();
	}

	return 0;
}
