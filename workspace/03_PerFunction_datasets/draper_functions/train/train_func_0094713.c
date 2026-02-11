ast_party_dialed_copy(struct ast_party_dialed *dest, const struct ast_party_dialed *src)
{
	if (dest == src) {

		return;
	}

	ast_free(dest->number.str);
	dest->number.str = ast_strdup(src->number.str);
	dest->number.plan = src->number.plan;
	ast_party_subaddress_copy(&dest->subaddress, &src->subaddress);
	dest->transit_network_select = src->transit_network_select;
}
