print_tableswitch_stmt(int lvl, struct string *str,
				  struct statement *stmt)
{
	int err;

	err = append_formatted(lvl, str, "TABLESWITCH:\n");
	if (err)
		goto out;

	err = append_tree_attr(lvl + 1, str, "index", stmt->expression);

	unsigned int count = stmt->table->high - stmt->table->low + 1;
	for (unsigned int i = 0; i < count; i++) {
		char case_name[16];

		sprintf(case_name, "case %d", stmt->table->low + i);
		err = append_simple_attr(lvl + 1, str, case_name, "bb %p",
					 stmt->table->bb_lookup_table[i]);
	}

out:
	return err;
}
