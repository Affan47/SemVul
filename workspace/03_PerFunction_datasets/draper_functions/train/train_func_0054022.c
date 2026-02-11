parseDataObjectSkinMeshHeader(SXMesh& mesh)
{
#ifdef _XREADER_DEBUG
	os::Printer::log("CXFileReader: Reading skin mesh header");
#endif

	if (!readHeadOfDataObject())
	{
		os::Printer::log("No opening brace in Skin Mesh header found in .x file", ELL_WARNING);
		os::Printer::log("Line", core::stringc(Line).c_str(), ELL_WARNING);
		return false;
	}

	mesh.MaxSkinWeightsPerVertex = readInt();
	mesh.MaxSkinWeightsPerFace = readInt();
	mesh.BoneCount = readInt();

	if (!BinaryFormat)
		getNextToken();

	if (!checkForClosingBrace())
	{
		os::Printer::log("No closing brace in skin mesh header in x file", ELL_WARNING);
		os::Printer::log("Line", core::stringc(Line).c_str(), ELL_WARNING);
		return false;
	}

	return true;
}
