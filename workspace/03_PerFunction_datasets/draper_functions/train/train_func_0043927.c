egg_editable_toolbar_show (EggEditableToolbar *etoolbar,
			   const char         *name)
{
  int i, n_toolbars;
  EggToolbarsModel *model = etoolbar->priv->model;

  g_return_if_fail (model != NULL);

  n_toolbars = egg_toolbars_model_n_toolbars (model);
  for (i = 0; i < n_toolbars; i++)
    {
      const char *toolbar_name;

      toolbar_name = egg_toolbars_model_toolbar_nth (model, i);
      if (strcmp (toolbar_name, name) == 0)
      {
        gtk_widget_show (get_dock_nth (etoolbar, i));
      }
    }
}
