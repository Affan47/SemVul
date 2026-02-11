CDB___bam_set_bt_compare(dbp, func)
	DB *dbp;
	int (*func) __P((const DBT *, const DBT *));
{
	BTREE *t;

	DB_ILLEGAL_AFTER_OPEN(dbp, "set_bt_compare");
	DB_ILLEGAL_METHOD(dbp, DB_OK_BTREE);

	t = dbp->bt_internal;


	t->bt_compare = func;
	if (t->bt_prefix == CDB___bam_defpfx)
		t->bt_prefix = NULL;

	return (0);
}
