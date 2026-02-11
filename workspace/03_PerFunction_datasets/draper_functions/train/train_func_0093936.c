evt_del_clicked(GtkWidget *wid, gpointer user)
{
	P_CmdSeq	*page = user;
	CmdSeq		*cs;
	GtkTreeIter	iter;

	if((cs = cmdseq_get_selected(page, &iter)) != NULL)
	{
		g_hash_table_remove(page->cmdseq, cs->name);
		csq_cmdseq_destroy(cs);
		gtk_list_store_remove(page->store, &iter);
		reset_widgets(page);
	}
}
