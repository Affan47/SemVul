add_format2index(enum ast_format_id id)
{
	if (format2index(id) != -1) {

		return 0;
	}

	ast_rwlock_wrlock(&tablelock);
	if (cur_max_index == (index_size)) {
		ast_rwlock_unlock(&tablelock);
		return -1;
	}
	__indextable[cur_max_index] = id;
	cur_max_index++;
	ast_rwlock_unlock(&tablelock);

	return 0;
}
