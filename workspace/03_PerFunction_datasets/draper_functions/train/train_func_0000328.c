printLogo(void)
{
	uint32_t versionMajor, versionMinor, versionPatch;
	MDynamicAudioNormalizer::getVersionInfo(versionMajor, versionMinor, versionPatch);

	const char *buildDate, *buildTime, *buildCompiler, *buildArch; bool buildDebug;
	MDynamicAudioNormalizer::getBuildInfo(&buildDate, &buildTime, &buildCompiler, &buildArch, buildDebug);

	PRINT(TXT("---------------------------------------------------------------------------\n"));

	PRINT(TXT("Dynamic Audio Normalizer, Version %u.%02u-%u, %s\n"), versionMajor, versionMinor, versionPatch, LINKAGE);
	PRINT(TXT("Copyright (c) 2015 LoRd_MuldeR <mulder2@gmx.de>. Some rights reserved.\n"));
	PRINT(TXT("Built on ") FMT_CHAR TXT(" at ") FMT_CHAR TXT(" with ") FMT_CHAR TXT(" for ") OS_TYPE TXT("-") FMT_CHAR TXT(".\n\n"), buildDate, buildTime, buildCompiler, buildArch);

	PRINT(TXT("This program is free software: you can redistribute it and/or modify\n"));
	PRINT(TXT("it under the terms of the GNU General Public License <http://www.gnu.org/>.\n"));
	PRINT(TXT("Note that this program is distributed with ABSOLUTELY NO WARRANTY.\n"));

	if(DYNAUDNORM_DEBUG)
	{
		PRINT(TXT("\n!!! DEBUG BUILD !!! DEBUG BUILD !!! DEBUG BUILD !!! DEBUG BUILD !!!\n"));
	}

	PRINT(TXT("---------------------------------------------------------------------------\n\n"));

	if((DYNAUDNORM_DEBUG) != buildDebug)
	{
		PRINT_ERR(TXT("Trying to use DEBUG library with RELEASE binary or vice versa!\n"));
		exit(EXIT_FAILURE);
	}
}
