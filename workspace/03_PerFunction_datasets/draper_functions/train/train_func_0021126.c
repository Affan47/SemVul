CBSPMeshFileLoader(scene::ISceneManager* smgr,
		io::IFileSystem* fs)
: FileSystem(fs), SceneManager(smgr)
{

	#ifdef _DEBUG
	setDebugName("CBSPMeshFileLoader");
	#endif

	if (FileSystem)
		FileSystem->grab();
}
