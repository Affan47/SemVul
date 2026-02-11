_e2_output_tab_remove (gpointer from, E2_ActionRuntime *art)
{
#ifdef E2_TABS_DETACH

	gint homecount = gtk_notebook_get_n_pages (GTK_NOTEBOOK (app.outbook));
	if (homecount == 1)
		return FALSE;


	gint index = gtk_notebook_get_current_page (GTK_NOTEBOOK (app.outbook));
	GtkWidget *sw = gtk_notebook_get_nth_page (GTK_NOTEBOOK (app.outbook), index);
	GList *member;
	for (member = app.tabslist; member != NULL; member = member->next)
	{
		if (((E2_OutputTabRuntime *)member->data)->scroll == sw)
			break;
	}
	if (member == NULL)
		return FALSE;

	gtk_notebook_remove_page (GTK_NOTEBOOK (app.outbook), index);
	if (--app.tabcount == 1)
		gtk_notebook_set_show_tabs (GTK_NOTEBOOK (app.outbook), FALSE);

	index = gtk_notebook_get_current_page (GTK_NOTEBOOK (app.outbook));
	sw = gtk_notebook_get_nth_page (GTK_NOTEBOOK (app.outbook), index);

	GList *newmember;
	for (newmember = app.tabslist; newmember != NULL; newmember = newmember->next)
	{
		if (((E2_OutputTabRuntime *)newmember->data)->scroll == sw)
			break;
	}
	if (newmember == NULL)
		return FALSE;


#else

	if (app.tabcount == 1)
		return FALSE;

	gint index = gtk_notebook_get_current_page (GTK_NOTEBOOK (app.outbook));
	gtk_notebook_remove_page (GTK_NOTEBOOK (app.outbook), index);
	if (--app.tabcount == 1)
		gtk_notebook_set_show_tabs (GTK_NOTEBOOK (app.outbook), FALSE);


	GList *member = g_list_nth (app.tabslist, index);
	GList *newmember;
	if (index == 0)
		newmember = member->next;
	else
		newmember = member->prev;
#endif
	E2_OutputTabRuntime *newtab = newmember->data;


	app.tab = *newtab;


	e2_command_retab2_children (member->data, newtab);

	curr_tab = newtab;

	if (((E2_OutputTabRuntime *)member->data)->origin_lastime!= NULL)
		g_free (((E2_OutputTabRuntime *)member->data)->origin_lastime);


	DEALLOCATE (E2_OutputTabRuntime, member->data);
	app.tabslist = g_list_delete_link (app.tabslist, member);
	return TRUE;
}
