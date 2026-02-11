writeImpl(std::ostream& ostr, const std::string& headerFileName)
{
	ostr << "#include \"" << headerFileName << "\"\n";
	writeImplIncludes(ostr);
	if (_page.getBool("page.buffered", false))
	{
		ostr << "#include \"Poco/StreamCopier.h\"\n";
		ostr << "#include <sstream>\n";
	}
	ostr << "\n\n";

	std::string decls(_page.implDecls().str());
	if (!decls.empty())
	{
		ostr << decls << "\n\n";
	}

	beginNamespace(ostr);
	writeConstructor(ostr);
	writeHandler(ostr);
	writeFactory(ostr);
	endNamespace(ostr);
	writeManifest(ostr);
}
