cb_build_section_name (cb_tree name, int sect_or_para)
{
	cb_tree x;

	if (name == cb_error_node) {
		return cb_error_node;
	}

	if (CB_REFERENCE (name)->word->count > 0) {
		x = CB_VALUE (CB_REFERENCE (name)->word->items);


		if (!CB_LABEL_P (x) || sect_or_para == 0
		    || (sect_or_para && CB_LABEL_P (x) && CB_LABEL (x)->is_section)) {
			redefinition_error (name);
			return cb_error_node;
		}
	}

	return name;
}
