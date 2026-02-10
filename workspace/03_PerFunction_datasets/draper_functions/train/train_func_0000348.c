ast_duplicate_ha(struct ast_ha *original)
{
	struct ast_ha *new_ha;

	if ((new_ha = ast_calloc(1, sizeof(*new_ha)))) {

		ast_copy_ha(original, new_ha);
	}

	return new_ha;
}
