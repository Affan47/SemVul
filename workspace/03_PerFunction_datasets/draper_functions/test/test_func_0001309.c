detail_instantiate(CONF_SECTION *conf, void **instance)
{
	struct detail_instance *inst;
	CONF_SECTION	*cs;

	inst = rad_malloc(sizeof(*inst));
	if (!inst) {
		return -1;
	}
	memset(inst, 0, sizeof(*inst));

	if (cf_section_parse(conf, inst, module_config) < 0) {
		detail_detach(inst);
		return -1;
	}


	cs = cf_section_sub_find(conf, "suppress");
	if (cs) {
		CONF_ITEM	*ci;

		inst->ht = fr_hash_table_create(detail_hash, detail_cmp,
						  NULL);

		for (ci = cf_item_find_next(cs, NULL);
		     ci != NULL;
		     ci = cf_item_find_next(cs, ci)) {
			const char	*attr;
			DICT_ATTR	*da;

			if (!cf_item_is_pair(ci)) continue;

			attr = cf_pair_attr(cf_itemtopair(ci));
			if (!attr) continue;

			da = dict_attrbyname(attr);
			if (!da) {
				radlog(L_INFO, "rlm_detail: WARNING: No such attribute %s: Cannot suppress printing it.", attr);
				continue;
			}


			if (!fr_hash_table_insert(inst->ht, da)) {
				radlog(L_ERR, "rlm_detail: Failed trying to remember %s", attr);
				detail_detach(inst);
				return -1;
			}
		}
	}


	*instance = inst;
	return 0;
}
