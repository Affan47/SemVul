evt_delrow_clicked(GtkWidget *wid, gpointer user)
{
	P_CmdSeq	*page = user;
	CmdSeq		*cs;
	GtkTreeIter	riter;
	CmdRow		*row;

	if((cs = cmdseq_get_selected(page, NULL)) == NULL)
		return;
	if((row = cmdrow_get_selected(page, &riter)) == NULL)
		return;
	csq_cmdseq_row_delete(cs, row);
	gtk_list_store_remove(page->dstore, &riter);
	page->modified = TRUE;
}
