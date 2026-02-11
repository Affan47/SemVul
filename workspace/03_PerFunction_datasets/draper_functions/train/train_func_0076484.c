glade_popup_action_populate_menu (GtkWidget *menu,
                                  GladeWidget *widget,
                                  GladeWidgetAction *action,
                                  gboolean packing)
{
  gint n;

  g_return_val_if_fail (GTK_IS_MENU (menu), 0);
  g_return_val_if_fail (GLADE_IS_WIDGET (widget), 0);

  g_return_val_if_fail (action == NULL || GLADE_IS_WIDGET_ACTION (action), 0);

  if (action)
    {
      GWActionClass *aclass = glade_widget_action_get_class (action);
      GList         *children = glade_widget_action_get_children (action);

      if (glade_widget_get_action (widget, aclass->path) &&
	  glade_widget_action_get_visible (action))
        return glade_popup_action_populate_menu_real (menu,
                                                      widget,
                                                      children,
                                                      G_CALLBACK
                                                      (glade_popup_menuitem_activated),
                                                      widget);

      if (glade_widget_get_pack_action (widget, aclass->path) &&
	  glade_widget_action_get_visible (action))
        return glade_popup_action_populate_menu_real (menu,
                                                      glade_widget_get_parent
                                                      (widget), children,
                                                      G_CALLBACK
                                                      (glade_popup_menuitem_packing_activated),
                                                      widget);

      return 0;
    }

  n = glade_popup_action_populate_menu_real (menu,
                                             widget,
                                             glade_widget_get_actions (widget),
                                             G_CALLBACK
                                             (glade_popup_menuitem_activated),
                                             widget);

  if (packing && glade_widget_get_pack_actions (widget))
    {
      if (n)
        {
          GtkWidget *separator = gtk_separator_menu_item_new ();
          gtk_menu_shell_append (GTK_MENU_SHELL (menu), separator);
          gtk_widget_show (separator);
        }

      n += glade_popup_action_populate_menu_real
	(menu, glade_widget_get_parent (widget),
	 glade_widget_get_pack_actions (widget),
	 G_CALLBACK (glade_popup_menuitem_packing_activated), widget);
    }

  return n;
}
