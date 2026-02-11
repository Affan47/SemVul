gedit_view_constructed (GObject *object)
{
	GeditView *view;
	GeditViewPrivate *priv;
	gboolean use_default_font;

	view = GEDIT_VIEW (object);
	priv = view->priv;


	use_default_font = g_settings_get_boolean (view->priv->editor_settings,
	                                           GEDIT_SETTINGS_USE_DEFAULT_FONT);


	if (!use_default_font)
	{
		gchar *editor_font;

		editor_font = g_settings_get_string (view->priv->editor_settings,
		                                     GEDIT_SETTINGS_EDITOR_FONT);

		gedit_view_set_font (view, FALSE, editor_font);

		g_free (editor_font);
	}
	else
	{
		gedit_view_set_font (view, TRUE, NULL);
	}

	g_settings_bind (priv->editor_settings,
	                 GEDIT_SETTINGS_DISPLAY_LINE_NUMBERS,
	                 view,
	                 "show-line-numbers",
	                 G_SETTINGS_BIND_GET);

	g_settings_bind (priv->editor_settings,
	                 GEDIT_SETTINGS_AUTO_INDENT,
	                 view,
	                 "auto-indent",
	                 G_SETTINGS_BIND_GET);

	g_settings_bind (priv->editor_settings,
	                 GEDIT_SETTINGS_TABS_SIZE,
	                 view,
	                 "tab-width",
	                 G_SETTINGS_BIND_GET);

	g_settings_bind (priv->editor_settings,
	                 GEDIT_SETTINGS_INSERT_SPACES,
	                 view,
	                 "insert-spaces-instead-of-tabs",
	                 G_SETTINGS_BIND_GET);

	g_settings_bind (priv->editor_settings,
	                 GEDIT_SETTINGS_DISPLAY_RIGHT_MARGIN,
	                 view,
	                 "show-right-margin",
	                 G_SETTINGS_BIND_GET);

	g_settings_bind (priv->editor_settings,
	                 GEDIT_SETTINGS_RIGHT_MARGIN_POSITION,
	                 view,
	                 "right-margin-position",
	                 G_SETTINGS_BIND_GET);

	g_settings_bind (priv->editor_settings,
	                 GEDIT_SETTINGS_HIGHLIGHT_CURRENT_LINE,
	                 view,
	                 "highlight-current-line",
	                 G_SETTINGS_BIND_GET);

	g_settings_bind (priv->editor_settings,
	                 GEDIT_SETTINGS_WRAP_MODE,
	                 view,
	                 "wrap-mode",
	                 G_SETTINGS_BIND_GET);

	g_settings_bind (priv->editor_settings,
	                 GEDIT_SETTINGS_SMART_HOME_END,
	                 view,
	                 "smart-home-end",
	                 G_SETTINGS_BIND_GET);

	g_object_set (G_OBJECT (view),
	              "indent_on_tab", TRUE,
	              NULL);

	G_OBJECT_CLASS (gedit_view_parent_class)->constructed (object);
}
