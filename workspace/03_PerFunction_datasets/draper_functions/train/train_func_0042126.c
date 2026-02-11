loadFromConfigFile(const mrpt::utils::CConfigFileBase  &source, const std::string &sct)
{
	MRPT_LOAD_CONFIG_VAR(enableSaveAs3DObject          , bool,   source,sct);
	MRPT_LOAD_CONFIG_VAR(enableObservationLikelihood   , bool,   source,sct);
	MRPT_LOAD_CONFIG_VAR(enableObservationInsertion    , bool,   source,sct);
}
