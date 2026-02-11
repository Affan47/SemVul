loadFromConfigFile(
	const mrpt::utils::CConfigFileBase	&iniFile,
	const string &section)
{
	rangeStd					= iniFile.read_float(section.c_str(),"rangeStd",rangeStd);
}
