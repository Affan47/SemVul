loadFromConfigFile(
	const mrpt::utils::CConfigFileBase  &iniFile,
	const std::string &section)
{
	MRPT_LOAD_CONFIG_VAR_CAST(likelihoodMethod, int, TLikelihoodMethod, iniFile, section);

    enableLikelihoodCache               = iniFile.read_bool(section,"enableLikelihoodCache",enableLikelihoodCache);

	LF_stdHit							= iniFile.read_float(section,"LF_stdHit",LF_stdHit);
	LF_zHit								= iniFile.read_float(section,"LF_zHit",LF_zHit);
	LF_zRandom							= iniFile.read_float(section,"LF_zRandom",LF_zRandom);
	LF_maxRange							= iniFile.read_float(section,"LF_maxRange",LF_maxRange);
	LF_decimation						= iniFile.read_int(section,"LF_decimation",LF_decimation);
	LF_maxCorrsDistance					= iniFile.read_float(section,"LF_maxCorrsDistance",LF_maxCorrsDistance);
	LF_useSquareDist					= iniFile.read_bool(section,"LF_useSquareDist",LF_useSquareDist);
	LF_alternateAverageMethod			= iniFile.read_bool(section,"LF_alternateAverageMethod",LF_alternateAverageMethod);

	MI_exponent							= iniFile.read_float(section,"MI_exponent",MI_exponent);
	MI_skip_rays						= iniFile.read_int(section,"MI_skip_rays",MI_skip_rays);
	MI_ratio_max_distance				= iniFile.read_float(section,"MI_ratio_max_distance",MI_ratio_max_distance);

	rayTracing_useDistanceFilter		= iniFile.read_bool(section,"rayTracing_useDistanceFilter",rayTracing_useDistanceFilter);
	rayTracing_stdHit					= iniFile.read_float(section,"rayTracing_stdHit",rayTracing_stdHit);

	consensus_takeEachRange				= iniFile.read_int(section,"consensus_takeEachRange",consensus_takeEachRange);
	consensus_pow						= iniFile.read_float(section,"consensus_pow",consensus_pow);

	iniFile.read_vector(section,"OWA_weights",OWA_weights,OWA_weights);
}
