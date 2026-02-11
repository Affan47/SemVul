p_selectionComboCallback (GtkWidget *widget)
{
  gint idValue;

  if(gap_debug)
  {
    printf("p_selectionComboCallback START\n");
  }

  gimp_int_combo_box_get_active (GIMP_INT_COMBO_BOX (widget), &idValue);

  if(gap_debug)
  {
    printf("p_selectionComboCallback idValue:%d\n", idValue);
  }
  glob_vals.alt_selection = idValue;

}
