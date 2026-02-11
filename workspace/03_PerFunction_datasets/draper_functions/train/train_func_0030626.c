edit_isspecial(int ch)
{

	if (strchr("\t ()<>[]{}#$&\\|?*;\'\"`~",ch))
		return 1;

	if (clex_data.shelltype == 1 && (ch == '!' || ch == ':'))
		return 1;

	if (*config_str(CFG_QUOTE) && strchr(config_str(CFG_QUOTE),ch))
		return 1;

	return 0;
}
