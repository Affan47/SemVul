dumpAsText() const
{
	mrpt::utils::CConfigFileMemory cfg;
	saveToConfigFile("",cfg);
	return cfg.getContent();
}
