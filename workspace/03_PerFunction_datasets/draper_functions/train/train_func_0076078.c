attr_index_idlistsize_config(Slapi_Entry *e, struct attrinfo *ai, char *returntext)
{
	int rc = 0;
	int ii;
	Slapi_Attr *idlattr;
	Slapi_Value *sval;
	struct index_idlistsizeinfo *idlinfo;

	slapi_entry_attr_find(e, NS_INDEX_IDLISTSCANLIMIT, &idlattr);
	if (!idlattr) {
		return rc;
	}
	for (ii = slapi_attr_first_value(idlattr, &sval); !rc && (ii != -1); ii = slapi_attr_next_value(idlattr, ii, &sval)) {
		idlinfo = (struct index_idlistsizeinfo *)slapi_ch_calloc(1, sizeof(struct index_idlistsizeinfo));
		if ((rc = attr_index_parse_idlistsize(ai, slapi_value_get_string(sval), idlinfo, returntext))) {
			attr_index_idlistsize_free(&idlinfo);
			attrinfo_delete_idlistinfo(&ai->ai_idlistinfo);
		} else {
			if (!ai->ai_idlistinfo) {
				ai->ai_idlistinfo = dl_new();
				dl_init(ai->ai_idlistinfo, 1);
			}
			dl_add(ai->ai_idlistinfo, idlinfo);
		}
	}
	return rc;
}
