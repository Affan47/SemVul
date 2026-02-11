refresh_projects_list_menu (GladeWindow *window)
{
	GladeWindowPrivate *p = window->priv;
	GList *actions, *l;
	GSList *group = NULL;
	gint n, i;
	guint id;

	if (p->projects_list_menu_ui_id != 0)
		gtk_ui_manager_remove_ui (p->ui, p->projects_list_menu_ui_id);


	actions = gtk_action_group_list_actions (p->projects_list_menu_actions);
	for (l = actions; l != NULL; l = l->next)
	{
		g_signal_handlers_disconnect_by_func (GTK_ACTION (l->data),
						      G_CALLBACK (projects_list_menu_activate_cb), window);
 		gtk_action_group_remove_action (p->projects_list_menu_actions, GTK_ACTION (l->data));
	}
	g_list_free (actions);

	n = gtk_notebook_get_n_pages (GTK_NOTEBOOK (p->notebook));

	id = (n > 0) ? gtk_ui_manager_new_merge_id (p->ui) : 0;


	for (i = 0; i < n; i++)
	{
		GtkWidget *view;
		GladeProject *project;
		GtkRadioAction *action;
		gchar action_name[32];
		gchar *project_name;
		gchar *tooltip;
		gchar accel[7];

		view = gtk_notebook_get_nth_page (GTK_NOTEBOOK (p->notebook), i);
		project = glade_design_view_get_project (GLADE_DESIGN_VIEW (view));


                g_snprintf (action_name, sizeof (action_name), "Tab_%d", i);
		project_name = get_formatted_project_name_for_display (project,
								       FORMAT_NAME_MARK_UNSAVED |
								       FORMAT_NAME_MIDDLE_TRUNCATE |
								       FORMAT_NAME_ESCAPE_UNDERSCORES);
		tooltip = format_project_list_item_tooltip (project);


                if (i < 10)
                        g_snprintf (accel, sizeof (accel), "<alt>%d", (i + 1) % 10);
                else
                        accel[0] = '\0';

		action = gtk_radio_action_new (action_name,
					       project_name,
					       tooltip,
					       NULL,
					       i);


		g_object_set_data (G_OBJECT (project), "project-list-action", action);
		g_object_set_data (G_OBJECT (action), "project", project);


		gtk_radio_action_set_group (action, group);
		group = gtk_radio_action_get_group (action);

		gtk_action_group_add_action_with_accel (p->projects_list_menu_actions,
							GTK_ACTION (action),
							accel);

		g_signal_connect (action, "activate",
				  G_CALLBACK (projects_list_menu_activate_cb),
				  window);

		gtk_ui_manager_add_ui (p->ui, id,
				       "/MenuBar/ProjectMenu/ProjectsListPlaceholder",
				       action_name, action_name,
				       GTK_UI_MANAGER_MENUITEM,
				       FALSE);

		if (GLADE_DESIGN_VIEW (view) == p->active_view)
			gtk_toggle_action_set_active (GTK_TOGGLE_ACTION (action), TRUE);

		g_object_unref (action);

		g_free (project_name);
		g_free (tooltip);
	}

	p->projects_list_menu_ui_id = id;
}
