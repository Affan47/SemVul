UndefineAll_op (GelCtx *ctx, GelETree * * a, gboolean *exception)
{
	GSList *li;
	GSList *list;

	list = g_slist_copy (d_getcontext_global ());

	for (li = list;
	     li != NULL;
	     li = li->next) {
		GelEFunc *f = li->data;
		GelToken *tok = f->id;
		if ( ! tok->protected_ &&
		    strcmp (tok->token, "Ans") != 0) {
			d_delete_global (tok);
		}
	}

	return gel_makenum_null ();
}
