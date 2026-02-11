find_option (const std::string &name, OptionType type)
{
	iterator opt = options_.find (name);
	if ((opt == options_.end()) || ((type != OPTTYPE_NONE)
									&& (opt->second->type() != type)))
		return NULL;
	return opt->second;
}
