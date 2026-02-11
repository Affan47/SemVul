combo_selected(GtkWidget *widget, gpointer window)
{
  int idx = gtk_combo_box_get_active (GTK_COMBO_BOX (opt_hime_edit_display));
  if (edit_disp[idx].keynum !=  HIME_EDIT_DISPLAY_ON_THE_SPOT) {
	  gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON(check_button_hime_on_the_spot_key), FALSE);
  }
}
