ast_codec_choose(struct ast_codec_pref *pref, struct ast_format_cap *cap, int find_best, struct ast_format *result)
{
	int x, slot, found = 0;
	size_t f_len = 0;
	const struct ast_format_list *f_list = ast_format_list_get(&f_len);

	for (x = 0; x < f_len; x++) {
		slot = pref->order[x];

		if (!slot)
			break;
		if (ast_format_cap_get_compatible_format(cap, &f_list[slot-1].format, result)) {
			found = 1;
			break;
		}
	}
	ast_format_list_destroy(f_list);
	if (found && (AST_FORMAT_GET_TYPE(result->id) == AST_FORMAT_TYPE_AUDIO)) {
		return result;
	}
	ast_format_clear(result);
	ast_debug(4, "Could not find preferred codec - %s\n", find_best ? "Going for the best codec" : "Returning zero codec");

	return find_best ? ast_best_codec(cap, result) : NULL;
}
