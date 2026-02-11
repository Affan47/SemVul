ast_party_id_set(struct ast_party_id *dest, const struct ast_party_id *src, const struct ast_set_party_id *update)
{
	if (dest == src) {

		return;
	}

	if (!update || update->name) {
		ast_party_name_set(&dest->name, &src->name);
	}
	if (!update || update->number) {
		ast_party_number_set(&dest->number, &src->number);
	}
	if (!update || update->subaddress) {
		ast_party_subaddress_set(&dest->subaddress, &src->subaddress);
	}

	if (src->tag && src->tag != dest->tag) {
		ast_free(dest->tag);
		dest->tag = ast_strdup(src->tag);
	}
}
