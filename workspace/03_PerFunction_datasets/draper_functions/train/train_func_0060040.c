midgard_core_dbjoin_new(void)
{
	MidgardDBJoin *mdbj = g_new(MidgardDBJoin, 1);

	mdbj->type = NULL;
	mdbj->typeid = 0;
	mdbj->klass = NULL;
	mdbj->left_table = NULL;
	mdbj->left_field = NULL;
	mdbj->left_klass = NULL;
	mdbj->right_table = NULL;
	mdbj->right_field = NULL;
	mdbj->right_klass = NULL;
	mdbj->left_tablefield = NULL;
	mdbj->right_tablefield = NULL;


	mdbj->left = NULL;
	mdbj->right = NULL;

	return mdbj;
}
