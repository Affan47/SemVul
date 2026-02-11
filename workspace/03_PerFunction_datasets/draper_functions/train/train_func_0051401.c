str_tr_unlocked(String *str, const char *from, const char *to, int option)
{
	StringTR table[1];

	if (!str || !from)
		return set_errno(EINVAL);

	table->locker = NULL;

	if (!tr_compile_table(table, from, to, option))
		return -1;

	return str_tr_compiled_unlocked(str, table);
}
