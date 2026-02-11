setDialRules(const char* name)
{
    if (delayConfig)
	dialRulesFile = name;
    else
	ServerConfig::setDialRules(name);
}
