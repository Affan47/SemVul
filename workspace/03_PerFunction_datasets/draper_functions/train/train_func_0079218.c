mov_selmode_menu_callback (GtkWidget *widget, t_mov_gui_stuff *mgp)
{
  gboolean l_sensitive;
  GtkWidget *spinbutton;
  gint value;

  gimp_int_combo_box_get_active (GIMP_INT_COMBO_BOX (widget), &value);
  pvals->src_selmode = value;

  if(mgp == NULL) return;

  l_sensitive = TRUE;
  if(pvals->src_selmode == GAP_MOV_SEL_IGNORE)
  {
    l_sensitive = FALSE;
  }

  if(mgp->sel_feather_radius_adj)
  {
    spinbutton = GTK_WIDGET(g_object_get_data (G_OBJECT (mgp->sel_feather_radius_adj), "spinbutton"));
    if(spinbutton)
    {
      gtk_widget_set_sensitive(spinbutton, l_sensitive);
    }
  }
  mov_set_instant_apply_request(mgp);
}
