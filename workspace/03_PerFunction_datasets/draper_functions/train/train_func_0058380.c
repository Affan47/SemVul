popup_menu_create (GstAddressList *list)
{
  GtkUIManager   *ui_manager;
  GtkActionGroup *action_group;
  GtkWidget      *popup;

  action_group = gtk_action_group_new ("MenuActions");
  gtk_action_group_set_translation_domain (action_group, NULL);
  gtk_action_group_add_actions (action_group, address_list_popup_menu_items, G_N_ELEMENTS (address_list_popup_menu_items), list);

  ui_manager = gtk_ui_manager_new ();
  gtk_ui_manager_insert_action_group (ui_manager, action_group, 0);

  if (!gtk_ui_manager_add_ui_from_string (ui_manager, address_list_ui_description, -1, NULL))
    return NULL;

  g_object_set_data (G_OBJECT (list), "ui-manager", ui_manager);
  popup = gtk_ui_manager_get_widget (ui_manager, "/MainMenu");

  return popup;
}
