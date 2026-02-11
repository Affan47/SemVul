abort_chat_clicked (GtkWidget * wid, gpointer none)
{
	struct DCC *dcc;
	GSList *start, *list;

	start = list = dcc_chat_get_selected ();
	for (; list; list = list->next)
	{
		dcc = list->data;
		dcc_abort (dcc->serv->front_session, dcc);
	}
	g_slist_free (start);
}
