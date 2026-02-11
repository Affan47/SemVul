debug_internal_parse_levels(const gchar* option_name,
		const gchar* value, gpointer data, GError** error)
{
	if (!value)
		return false;
	debug_internal::DebugCmdArgs* args = static_cast<debug_internal::DebugCmdArgs*>(data);
	std::string levels = value;
	hz::string_split(levels, ',', args->debug_levels, true);

	return true;
}
