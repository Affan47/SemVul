get_envCmd()
{
	if (_nword != 4) {
		NUMBER_WORDS_ERROR;
		demonstrate_command_usage();
		return false;
	}
	std::string the_syn(_word[2]);
	un_double_quote(the_syn);
	un_double_slash(the_syn);
	de_reference(the_syn);
	if (!is_syn(the_syn)) {
		err("No synonym name given");
		demonstrate_command_usage();
		return false;
	}
	std::string the_env_var(_word[3]);
	un_double_quote(the_env_var);
	de_reference(the_env_var);
	char *result = egetenv(the_env_var.c_str());
	if (result == NULL) {
		if (!put_syn(the_syn.c_str(), "", true)) {
			gr_Error("Ran out of storage");
			return false;
		}
		warning("No environment variable called `\\", the_env_var.c_str(), "' exits.", "\\");
	} else {
		if (!put_syn(the_syn.c_str(), result, true)) {
			gr_Error("Ran out of storage");
			return false;
		}
	}
	return true;
}
