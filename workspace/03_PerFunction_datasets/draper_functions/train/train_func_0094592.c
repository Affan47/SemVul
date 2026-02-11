script_set_userfunc(const char *name, struct script_code *code)
{
	if(!userfunc_db)
		userfunc_db = strdb_init(50);

	return (struct script_code *)strdb_insert(userfunc_db, name, code);
}
