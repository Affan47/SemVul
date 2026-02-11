to_string (const std::string &name, gboolean respect_update)
{
	Option *option = find_option (name);
	if (!option)
		return std::string ("");
	if ((option->flags() & OPTFLG_UPDATE) && respect_update)
		option_update (option);
	return option->to_string ();
}
