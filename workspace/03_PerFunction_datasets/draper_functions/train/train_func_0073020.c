writeImplIncludes(std::ostream& ostr)
{
	CodeWriter::writeImplIncludes(ostr);
	if (page().has("page.session"))
	{
		ostr << "#include \"Poco/OSP/Web/WebSession.h\"\n";
		ostr << "#include \"Poco/OSP/Web/WebSessionManager.h\"\n";
		ostr << "#include \"Poco/OSP/ServiceRegistry.h\"\n";
	}
}
