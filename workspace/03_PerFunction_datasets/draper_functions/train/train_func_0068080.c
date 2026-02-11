pop_filename(void)
{
	name_depth--;
	if (name_depth < MAX_DEPTH) {
		*name_component[name_depth] = '\0';
		if (!name_depth) {
			current_name[0] = '/';
			current_name[1] = '\0';
		}
	}
}
