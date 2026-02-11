loadScene(io::IReadFile* file, ISceneUserDataSerializer* userDataSerializer)
{
	if (!file)
	{
		os::Printer::log("Unable to open scene file", ELL_ERROR);
		_IRR_IMPLEMENT_MANAGED_MARSHALLING_BUGFIX;
		return false;
	}

	io::IXMLReader* reader = FileSystem->createXMLReader(file);
	if (!reader)
	{
		os::Printer::log("Scene is not a valid XML file", file->getFileName(), ELL_ERROR);
		_IRR_IMPLEMENT_MANAGED_MARSHALLING_BUGFIX;
		return false;
	}


	bool oldColladaSingleMesh = getParameters()->getAttributeAsBool(COLLADA_CREATE_SCENE_INSTANCES);
	getParameters()->setAttribute(COLLADA_CREATE_SCENE_INSTANCES, false);


	while(reader->read())
	{
		readSceneNode(reader, 0, userDataSerializer);
	}


	getParameters()->setAttribute(COLLADA_CREATE_SCENE_INSTANCES, oldColladaSingleMesh);


	reader->drop();
	return true;
}
