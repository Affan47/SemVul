cb_check_numeric_value (cb_tree x)
{
	if (x == cb_error_node) {
		return cb_error_node;
	}

	if (CB_TREE_CATEGORY (x) == CB_CATEGORY_NUMERIC) {
		return x;
	}

	cb_error_x (x, _("'%s' is not a numeric value"), cb_name (x));
	return cb_error_node;
}
