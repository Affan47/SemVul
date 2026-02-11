loadGUI(io::IReadFile* file, IGUIElement* parent)
{
	if (!file)
	{
		os::Printer::log("Unable to open GUI file", ELL_ERROR);
		_IRR_IMPLEMENT_MANAGED_MARSHALLING_BUGFIX;
		return false;
	}

	io::IXMLReader* reader = FileSystem->createXMLReader(file);
	if (!reader)
	{
		os::Printer::log("GUI is not a valid XML file", file->getFileName(), ELL_ERROR);
		_IRR_IMPLEMENT_MANAGED_MARSHALLING_BUGFIX;
		return false;
	}


	while(reader->read())
	{
		readGUIElement(reader, parent);
	}


	reader->drop();
	return true;
}
