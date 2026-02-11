init_jlist_win(void)
{
	unsigned  cnt;
	GtkTreeSelection *sel;
	GType	coltypes[NUM_JOB_ELS];


	for  (cnt = 0;  cnt < NUM_JOB_ELS;  cnt++)  {
		jlist_els[cnt].msgtext = gprompt(jlist_els[cnt].msgcode);
		coltypes[cnt] = jlist_els[cnt].type;
	}

	for  (cnt = 0;  cnt < NUM_JOB_ELS;  cnt++)
		jlist_els[cnt].descr = gprompt(jlist_els[cnt].msgcode + 1530 - 1490);


	jwid = gtk_tree_view_new();
	jobflds.view = jwid;
	jobflds.is_sorted = 0;
	jlist_store = gtk_list_store_newv(NUM_JOB_ELS, coltypes);
	gtk_tree_view_set_model(GTK_TREE_VIEW(jwid), GTK_TREE_MODEL(jlist_store));
	if  (def_jobflds)
		set_tview_attribs(&jobflds, def_jobflds, ndef_jobflds);
	else
		set_tview_attribs(&jobflds, defflds, NDEFFLDS);
	sel = gtk_tree_view_get_selection(GTK_TREE_VIEW(jwid));
	gtk_tree_selection_set_mode(sel, GTK_SELECTION_SINGLE);
	localptr = gprompt(304);
	gtk_tree_view_set_headers_clickable(GTK_TREE_VIEW(jwid), TRUE);
}
