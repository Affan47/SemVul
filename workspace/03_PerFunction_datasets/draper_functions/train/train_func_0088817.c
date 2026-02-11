__bam_print_cursor(dbc)
	DBC *dbc;
{
	static const FN fn[] = {
		{ C_DELETED,	"C_DELETED" },
		{ C_RECNUM,	"C_RECNUM" },
		{ C_RENUMBER,	"C_RENUMBER" },
		{ 0,		NULL }
	};
	ENV *env;
	BTREE_CURSOR *cp;

	env = dbc->env;
	cp = (BTREE_CURSOR *)dbc->internal;

	STAT_ULONG("Overflow size", cp->ovflsize);
	if (dbc->dbtype == DB_RECNO)
		STAT_ULONG("Recno", cp->recno);
	STAT_ULONG("Order", cp->order);
	__db_prflags(env, NULL, cp->flags, fn, NULL, "\tInternal Flags");
}
