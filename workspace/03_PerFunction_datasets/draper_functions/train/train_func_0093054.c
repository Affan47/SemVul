read_ornament_map()
{

	set_last_error_code(ERR_NOMEM);
	struct llist *ornament_map = create_llist();
	if (NULL == ornament_map) return NULL;

	char *line;
	while ((line = read_line(ornament_map_file)) != NULL) {

		if ('#' == line[0] || is_all_whitespace(line)) {
			free(line);
			continue;
		}

		struct ornament_map_element *oel = malloc(
				sizeof(struct ornament_map_element));
		if (NULL == oel) return NULL;


		struct llist *label_list = create_llist();
		if (NULL == label_list) return NULL;
		struct word_tokenizer *wtok = create_word_tokenizer(line);
		if (NULL == wtok) return NULL;

		set_last_error_code(ERR_ORN_MAP_SYNTAX);
		char *ornament = wt_next_noquote(wtok);
		if (NULL == ornament) return NULL;
		char *type = wt_next(wtok);
		if (NULL == type) return NULL;

		set_last_error_code(ERR_NOMEM);
		char *label;
		while ((label = wt_next(wtok)) != NULL) {
			if (! append_element(label_list, label)) return NULL;
		}
		destroy_word_tokenizer(wtok);
		free(line);

		if (0 == label_list->count) {
				set_last_error_code(ERR_ORN_MAP_SYNTAX);
				return NULL;
		}
		oel->group_type = get_group_type(type);
		if (UNKNOWN == oel->group_type) {
			fprintf (stderr, "WARNING: unknown group type '%s' (ignored)\n", type);
			free(oel);
			free(type);
			destroy_llist(label_list);
			continue;
		}
		oel->ornament = ornament;

		if (strstr(ornament, "<text") == ornament)
			oel->text = true;
		else
			oel->text = false;
		oel->labels = label_list;
		if (! append_element(ornament_map, oel))
			return NULL;

		free(type);
	}

	fclose(ornament_map_file);

	switch (read_line_status) {
		case READLINE_EOF:
			return ornament_map;
		case READLINE_ERROR:
			return NULL;
		default:
			assert(0);
	}
}
