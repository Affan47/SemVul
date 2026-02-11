key_changed_callback(GConfClient* client,
                     guint cnxn_id,
                     GConfEntry *entry,
                     gpointer user_data)
{
  GtkWidget* label;

  label = GTK_WIDGET(user_data);

  if (gconf_entry_get_value (entry) == NULL)
    {
      gtk_label_set_text (GTK_LABEL (label), "<unset>");
    }
  else
    {
      if (gconf_entry_get_value (entry)->type == GCONF_VALUE_STRING)
        {
          gtk_label_set_text (GTK_LABEL (label),
                              gconf_value_get_string (gconf_entry_get_value (entry)));
        }
      else
        {
          gtk_label_set_text (GTK_LABEL (label), "<wrong type>");
        }
    }
}
