parseDataObjectTemplate()
{
#ifdef _XREADER_DEBUG
	os::Printer::log("CXFileReader: Reading template");
#endif


	core::stringc name;

	if (!readHeadOfDataObject(&name))
	{
		os::Printer::log("Left delimiter in template data object missing.",
			name.c_str(), ELL_WARNING);
		os::Printer::log("Line", core::stringc(Line).c_str(), ELL_WARNING);
		return false;
	}


	getNextToken();


	while(true)
	{
		core::stringc s = getNextToken();

		if (s == "}")
			break;

		if (s.size() == 0)
			return false;
	}

	return true;
}
