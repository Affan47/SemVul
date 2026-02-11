scope_declare(struct scope *s, const char *token, const size_t len, struct parser_state *state)
{
	const struct cli_element *el = cli_hashtab_insert(&s->id_map, token, len, state->var_uniq++);


	return el ? el->key : NULL;
}
