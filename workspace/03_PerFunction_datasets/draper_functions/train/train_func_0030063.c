matrix_resize(int init)
{
	struct translator_path **tmp_matrix = NULL;
	int *tmp_table = NULL;
	int old_index;
	int x;

	AST_RWLIST_WRLOCK(&translators);
	ast_rwlock_wrlock(&tablelock);

	old_index = index_size;
	if (init) {
		index_size += INIT_INDEX;
	} else {
		index_size += GROW_INDEX;
	}


	if (!(tmp_matrix = ast_calloc(1, sizeof(struct translator_path *) * (index_size)))) {
		goto resize_cleanup;
	}

	for (x = 0; x < index_size; x++) {
		if (!(tmp_matrix[x] = ast_calloc(1, sizeof(struct translator_path) * (index_size)))) {
			goto resize_cleanup;
		}
	}


	if (!(tmp_table = ast_calloc(1, sizeof(int) * index_size))) {
		goto resize_cleanup;
	}


	if (!init) {
		for (x = 0; x < old_index; x++) {
			ast_free(__matrix[x]);
		}
		ast_free(__matrix);

		memcpy(tmp_table, __indextable, sizeof(int) * old_index);
		ast_free(__indextable);
	}


	__matrix = tmp_matrix;
	__indextable = tmp_table;

	matrix_rebuild(0);
	ast_rwlock_unlock(&tablelock);
	AST_RWLIST_UNLOCK(&translators);

	return 0;

resize_cleanup:
	ast_rwlock_unlock(&tablelock);
	AST_RWLIST_UNLOCK(&translators);
	if (tmp_matrix) {
		for (x = 0; x < index_size; x++) {
			ast_free(tmp_matrix[x]);
		}
		ast_free(tmp_matrix);
	}
	ast_free(tmp_table);

	return -1;
}
