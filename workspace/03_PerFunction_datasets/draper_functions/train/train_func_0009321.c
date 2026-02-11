chanview_find_parent (chanview *cv, void *family, GtkTreeIter *search_iter, chan *avoid)
{
	chan *search_ch;


	if (gtk_tree_model_get_iter_first (GTK_TREE_MODEL (cv->store), search_iter))
	{
		do
		{
			gtk_tree_model_get (GTK_TREE_MODEL (cv->store), search_iter,
									  COL_CHAN, &search_ch, -1);
			if (family == search_ch->family && search_ch != avoid
)
				return TRUE;
		}
		while (gtk_tree_model_iter_next (GTK_TREE_MODEL (cv->store), search_iter));
	}

	return FALSE;
}
