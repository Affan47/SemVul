WriteErrorsToFile(std::string staFileName,
	std::string staGdlFile, std::string staInputFontFile,
	std::string staOutputFile, std::string staOutputFamily, std::string staVersion,
	bool fSepCtrlFile)
{
	std::ofstream strmOut;
	strmOut.open(staFileName.c_str());
	if (strmOut.fail())
	{
		g_errorList.AddError(106, NULL,
			"Error in writing to file ",
			std::string(staFileName));
		return;
	}

	WriteErrorsToStream(strmOut, staGdlFile, staInputFontFile, staOutputFile, staOutputFamily,
		staVersion, fSepCtrlFile);
	strmOut.close();
}
