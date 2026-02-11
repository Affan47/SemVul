parseDataObjectMeshTextureCoords(SXMesh &mesh)
{
#ifdef _XREADER_DEBUG
	os::Printer::log("CXFileReader: reading mesh texture coordinates");
#endif

	if (!readHeadOfDataObject())
	{
		os::Printer::log("No opening brace in Mesh Texture Coordinates found in x file", ELL_WARNING);
		os::Printer::log("Line", core::stringc(Line).c_str(), ELL_WARNING);
		return false;
	}

	const u32 nCoords = readInt();
	for (u32 i=0; i<nCoords; ++i)
		readVector2(mesh.Vertices[i].TCoords);

	if (!checkForTwoFollowingSemicolons())
	{
		os::Printer::log("No finishing semicolon in Mesh Texture Coordinates Array found in x file", ELL_WARNING);
		os::Printer::log("Line", core::stringc(Line).c_str(), ELL_WARNING);
	}

	if (!checkForClosingBrace())
	{
		os::Printer::log("No closing brace in Mesh Texture Coordinates Array found in x file", ELL_WARNING);
		os::Printer::log("Line", core::stringc(Line).c_str(), ELL_WARNING);
		return false;
	}

	return true;
}
