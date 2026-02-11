gel_subst_local_vars (GSList *funclist, GSList **toklist)
{
	GSList *li;
	GSList *prev;

	li = *toklist;
	prev = NULL;
	while (li != NULL) {
		GelToken *id = li->data;
		GelEFunc *func = d_lookup_local (id);
		if (func != NULL &&
		    ! func->is_local) {
			GSList *tmp;
			GelEFunc *f = d_copyfunc (func);
			if ( ! f->on_subst_list)
				f->context = -1;
			funclist = g_slist_prepend (funclist, f);

			tmp = li;
			li = li->next;
			if (prev != NULL) {
				prev->next = g_slist_remove_link (prev->next, tmp);
			} else {
				*toklist = g_slist_remove_link (*toklist, tmp);
			}
		} else {
			prev = li;
			li = li->next;
		}
	}
	return funclist;
}
