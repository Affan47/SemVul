log_func (Group         g_,
		  size_t        indent_level_,
		  const string& func_name_,
		  marker_t      type_)
{
    if (! group_enabled (g_)) {
		return 0;
    }

    add_timestamp (std::cerr);
    indent_func_name (std::cout, func_name_, indent_level_, type_);

	if (type_ == FUNC_ENTRY) {
		std::cout << "---v---\n";
	}
	else if (type_ == FUNC_EXIT) {
		std::cout << "---^---\n";
	}

    return 0;
}
