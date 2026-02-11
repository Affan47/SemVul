qpol_extended_image_destroy(qpol_extended_image_t ** ext)
{
	size_t i = 0;

	if (!ext || !(*ext))
		return;

	qpol_syn_rule_table_destroy(&((*ext)->syn_rule_table));

	for (i = 0; i < (*ext)->master_list_sz; i++) {
		qpol_syn_rule_destroy(&((*ext)->syn_rule_master_list[i]));
	}
	free((*ext)->syn_rule_master_list);

	free(*ext);
	*ext = NULL;
}
