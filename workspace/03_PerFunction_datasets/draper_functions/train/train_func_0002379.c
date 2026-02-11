gdict_window_cmd_edit_select_all (GSimpleAction *action,
                                  GVariant      *parameter,
                                  gpointer       user_data)
{
  GdictWindow *window = user_data;

  g_assert (GDICT_IS_WINDOW (window));

  if (gtk_widget_has_focus (window->entry))
    gtk_editable_select_region (GTK_EDITABLE (window->entry), 0, -1);
  else
    gdict_defbox_select_all (GDICT_DEFBOX (window->defbox));
}
