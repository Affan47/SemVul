toolbar_changed_cb (EggToolbarsModel   *model,
	            int                 position,
	            EggEditableToolbar *etoolbar)
{
  GtkWidget *toolbar;
  EggTbModelFlags flags;
  GtkToolbarStyle style;

  flags = egg_toolbars_model_get_flags (model, position);
  toolbar = get_toolbar_nth (etoolbar, position);

  if (flags & EGG_TB_MODEL_ICONS)
  {
    style = GTK_TOOLBAR_ICONS;
  }
  else if (flags & EGG_TB_MODEL_TEXT)
  {
    style = GTK_TOOLBAR_TEXT;
  }
  else if (flags & EGG_TB_MODEL_BOTH)
  {
    style = GTK_TOOLBAR_BOTH;
  }
  else if (flags & EGG_TB_MODEL_BOTH_HORIZ)
  {
    style = GTK_TOOLBAR_BOTH_HORIZ;
  }
  else
  {
    gtk_toolbar_unset_style (GTK_TOOLBAR (toolbar));
    if (position == 0 && etoolbar->priv->fixed_toolbar)
      {
        unset_fixed_style (etoolbar);
      }
    return;
  }

  gtk_toolbar_set_style (GTK_TOOLBAR (toolbar), style);
  if (position == 0 && etoolbar->priv->fixed_toolbar)
    {
      set_fixed_style (etoolbar, style);
    }

  toolbar_visibility_refresh (etoolbar);
}
