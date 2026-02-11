add_constraint(struct isl_stream *s,
	struct vars *v, __isl_take isl_map *map, int rational)
{
	struct isl_token *tok = NULL;
	isl_pw_aff_list *list1 = NULL, *list2 = NULL;
	isl_set *set;

	set = isl_map_wrap(map);
	list1 = accept_affine_list(s, isl_set_get_space(set), v);
	if (!list1)
		goto error;
	tok = isl_stream_next_token(s);
	if (!is_comparator(tok)) {
		isl_stream_error(s, tok, "missing operator");
		if (tok)
			isl_stream_push_token(s, tok);
		tok = NULL;
		goto error;
	}
	for (;;) {
		list2 = accept_affine_list(s, isl_set_get_space(set), v);
		if (!list2)
			goto error;

		set = construct_constraints(set, tok->type, list1, list2,
						rational);
		isl_token_free(tok);
		isl_pw_aff_list_free(list1);
		list1 = list2;

		tok = isl_stream_next_token(s);
		if (!is_comparator(tok)) {
			if (tok)
				isl_stream_push_token(s, tok);
			break;
		}
	}
	isl_pw_aff_list_free(list1);

	return isl_set_unwrap(set);
error:
	if (tok)
		isl_token_free(tok);
	isl_pw_aff_list_free(list1);
	isl_pw_aff_list_free(list2);
	isl_set_free(set);
	return NULL;
}
