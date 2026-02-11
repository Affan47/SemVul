line_type_dialog_linetype_change(GtkWidget *w, gpointer data)
{
  struct line_type_data *line_type_data = (struct line_type_data*) data;
  GtkWidget *menuitem;
  gboolean activate_length_entry, activate_space_entry;
  gint type;

  menuitem = gtk_menu_get_active (
    GTK_MENU (gtk_option_menu_get_menu (
                GTK_OPTION_MENU (line_type_data->line_type))));

  type = GPOINTER_TO_INT(
    gtk_object_get_data (GTK_OBJECT (menuitem), "linetype"));
  switch(type) {
      case(TYPE_SOLID):
        activate_length_entry = FALSE;
        activate_space_entry  = FALSE;
        break;
      case(TYPE_DOTTED):
        activate_length_entry = FALSE;
        activate_space_entry  = TRUE;
        break;
      case(TYPE_DASHED):
      case(TYPE_CENTER):
      case(TYPE_PHANTOM):
        activate_length_entry = TRUE;
        activate_space_entry  = TRUE;
        break;
      default:
        activate_length_entry = TRUE;
        activate_space_entry  = TRUE;
  }

  gtk_widget_set_sensitive (line_type_data->space_entry,
                            activate_space_entry);
  gtk_widget_set_sensitive (line_type_data->length_entry,
                            activate_length_entry);

  return(0);
}
