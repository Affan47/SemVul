loadFromConfigFile(
	const mrpt::utils::CConfigFileBase  &iniFile,
	const std::string &section)
{
	MRPT_LOAD_CONFIG_VAR( filterByHeight,	bool, iniFile, section )
	MRPT_LOAD_CONFIG_VAR( z_min,			float, iniFile, section )
	MRPT_LOAD_CONFIG_VAR( z_max,			float, iniFile, section )
	string aux = iniFile.read_string(section, "colorMap", "jet");

	if(strCmp(aux,"jet") )
		colorMap = cmJET;
	else if(strCmp(aux,"grayscale") )
		colorMap = cmGRAYSCALE;
}
