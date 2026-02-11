GetAttr(const std::string& name)
{
	if ( arg_list.find(name) != arg_list.end() )
		return arg_list[name];
	return empty_str;
}
