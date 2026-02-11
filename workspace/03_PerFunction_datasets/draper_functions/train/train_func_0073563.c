view_diff_add_ui (GiggleView   *view,
		  GtkUIManager *manager)
{
	static const char layout[] =
		"<ui>"
		"  <menubar name='MainMenubar'>"
		"    <menu action='GoMenu'>"
		"      <separator />"
		"      <menuitem action='ViewDiffPreviousChange' />"
		"      <menuitem action='ViewDiffNextChange' />"
		"    </menu>"
		"  </menubar>"
		"  <toolbar name='ViewHistoryToolbar'>"
		"    <placeholder name='Actions'>"
		"      <toolitem action='ViewDiffPreviousChange' />"
		"      <toolitem action='ViewDiffNextChange' />"
		"      <toolitem action='ViewDiffRevisionInfo' />"
		"     </placeholder>"
		"  </toolbar>"
		"</ui>";

	static const GtkActionEntry actions[] = {
		{ "ViewDiffPreviousChange", GTK_STOCK_GO_UP,
		  N_("_Previous Change"), "<alt>Up", N_("View previous change"),
		  G_CALLBACK (view_diff_previous_change_cb)
		},
		{ "ViewDiffNextChange", GTK_STOCK_GO_DOWN,
		  N_("_Next Change"), "<alt>Down", N_("View next change"),
		  G_CALLBACK (view_diff_next_change_cb)
		},
	};

	GiggleViewDiffPriv *priv;
	int                 n_hunks;

	priv = GET_PRIV (view);

	priv->view_shell_separator = gtk_ui_manager_get_widget (manager, PATH_VIEW_SHELL_SEPARATOR);

	if (!priv->action_group) {
		n_hunks = giggle_diff_view_get_n_hunks (GIGGLE_DIFF_VIEW (priv->diff_view));
		priv->action_group = gtk_action_group_new (giggle_view_get_name (view));

		gtk_action_group_set_sensitive (priv->action_group, n_hunks > 0);
		gtk_action_group_set_translation_domain (priv->action_group, GETTEXT_PACKAGE);
		gtk_action_group_add_actions (priv->action_group, actions, G_N_ELEMENTS (actions), view);
		gtk_action_group_add_action (priv->action_group, priv->revision_info);

		gtk_ui_manager_insert_action_group (manager, priv->action_group, 0);
		gtk_ui_manager_add_ui_from_string (manager, layout, G_N_ELEMENTS (layout) - 1, NULL);
		gtk_ui_manager_ensure_update (manager);
	}

	if (priv->view_shell_separator) {
		gtk_tool_item_set_expand (GTK_TOOL_ITEM (priv->view_shell_separator), FALSE);
		gtk_widget_hide (priv->view_shell_separator);
	}

	gtk_action_group_set_visible (priv->action_group, TRUE);
}
