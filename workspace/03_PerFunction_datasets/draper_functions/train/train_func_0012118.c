userSupportDir(FileName const & default_user_support_dir,
	string const & command_line_user_support_dir, FileName & result)
{

	result = abs_path_from_command_line(command_line_user_support_dir);
	if (!result.empty())
		return true;


	result = extract_env_var_dir(LYX_USERDIR_VER);
	if (!result.empty())
		return true;


	result = default_user_support_dir;
	return false;
}
