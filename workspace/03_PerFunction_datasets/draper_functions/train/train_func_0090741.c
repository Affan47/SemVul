create_auto_select_by_phrase_opts(GtkWidget **out, int val)
{
  *out = gtk_combo_box_new_text ();

  int i, current_idx=0;

  for(i=0; auto_select_by_phrase_opts[i].str; i++) {
    if (auto_select_by_phrase_opts[i].num == val)
      current_idx = i;
    gtk_combo_box_append_text (GTK_COMBO_BOX_TEXT (*out), _(auto_select_by_phrase_opts[i].str));
  }

  gtk_combo_box_set_active (GTK_COMBO_BOX (*out), current_idx);

  return *out;
}
