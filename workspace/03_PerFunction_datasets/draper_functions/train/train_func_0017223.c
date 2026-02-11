dict_index_build_internal_non_clust(

	const dict_table_t*	table,
	dict_index_t*		index)

{
	dict_field_t*	field;
	dict_index_t*	new_index;
	dict_index_t*	clust_index;
	ulint		i;
	ibool*		indexed;

	ut_ad(table && index);
	ut_ad(!dict_index_is_clust(index));
	ut_ad(mutex_own(&(dict_sys->mutex)));
	ut_ad(table->magic_n == DICT_TABLE_MAGIC_N);


	clust_index = UT_LIST_GET_FIRST(table->indexes);

	ut_ad(clust_index);
	ut_ad(dict_index_is_clust(clust_index));
	ut_ad(!(clust_index->type & DICT_UNIVERSAL));


	new_index = dict_mem_index_create(
		table->name, index->name, index->space, index->type,
		index->n_fields + 1 + clust_index->n_uniq);


	new_index->n_user_defined_cols = index->n_fields;

	new_index->id = index->id;


	dict_index_copy(new_index, index, table, 0, index->n_fields);


	indexed = mem_zalloc(table->n_cols * sizeof *indexed);


	for (i = 0; i < new_index->n_def; i++) {

		field = dict_index_get_nth_field(new_index, i);


		if (field->prefix_len == 0) {

			indexed[field->col->ind] = TRUE;
		}
	}


	for (i = 0; i < clust_index->n_uniq; i++) {

		field = dict_index_get_nth_field(clust_index, i);

		if (!indexed[field->col->ind]) {
			dict_index_add_col(new_index, table, field->col,
					   field->prefix_len);
		}
	}

	mem_free(indexed);

	if (dict_index_is_unique(index)) {
		new_index->n_uniq = index->n_fields;
	} else {
		new_index->n_uniq = new_index->n_def;
	}


	new_index->n_fields = new_index->n_def;

	new_index->cached = TRUE;

	return(new_index);
}
