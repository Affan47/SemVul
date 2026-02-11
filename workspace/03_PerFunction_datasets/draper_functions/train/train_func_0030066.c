setRaw(const std::string& key, const std::string& value)
{
	std::string translatedKey = translateKey(key);
	_pConfig->setRaw(translatedKey, value);
}
