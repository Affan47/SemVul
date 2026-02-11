loadFromConfigFile_map_specific(const mrpt::utils::CConfigFileBase  &source, const std::string &sectionNamePrefix)
{

	const std::string sSectCreation = sectionNamePrefix+string("_creationOpts");
	MRPT_LOAD_CONFIG_VAR(min_x, double,   source,sSectCreation);
	MRPT_LOAD_CONFIG_VAR(max_x, double,   source,sSectCreation);
	MRPT_LOAD_CONFIG_VAR(min_y, double,   source,sSectCreation);
	MRPT_LOAD_CONFIG_VAR(max_y, double,   source,sSectCreation);
	MRPT_LOAD_CONFIG_VAR(resolution, double,   source,sSectCreation);

	insertionOpts.loadFromConfigFile(source, sectionNamePrefix+string("_insertOpts") );
}
