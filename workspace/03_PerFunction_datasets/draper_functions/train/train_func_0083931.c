gnac_profiles_utils_set_value_combo(GtkWidget   *combo,
                                    const gchar *value)
{
  ComboValues *combo_values = g_object_get_data(G_OBJECT(combo), "combo-values");
  GList *values = combo_values->values;

  if (!value) value = combo_values->default_value;

  gint index = 0;
  while (values) {
    if (gnac_utils_str_equal(value,  values->data)) {
      gtk_combo_box_set_active(GTK_COMBO_BOX(combo), index);
    }

    values = g_list_next(values);
    index++;
  }
}
