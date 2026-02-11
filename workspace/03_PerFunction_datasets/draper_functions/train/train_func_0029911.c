tree_prepare(struct view *view)
{
	if (view->lines == 0 && opt_prefix[0]) {
		char *pos = opt_prefix;

		while (pos && *pos) {
			char *end = strchr(pos, '/');

			if (end)
				*end = 0;
			push_tree_stack_entry(pos, 0);
			pos = end;
			if (end) {
				*end = '/';
				pos++;
			}
		}

	} else if (strcmp(view->vid, view->id)) {
		opt_path[0] = 0;
	}

	return init_io_rd(&view->io, view->ops->argv, opt_cdup, FORMAT_ALL);
}
