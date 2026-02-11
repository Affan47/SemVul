get_cd_name()
{
	if (impl) return impl->get_cd_name();
	return std::string();
}
