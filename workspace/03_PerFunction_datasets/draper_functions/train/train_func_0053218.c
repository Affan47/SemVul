dpms_combo_changed_cb (GtkWidget *widget, CcScreenPanel *self)
{
  GtkTreeIter iter;
  GtkTreeModel *model;
  gint value;
  gboolean ret;


  ret = gtk_combo_box_get_active_iter (GTK_COMBO_BOX(widget), &iter);
  if (!ret)
    return;


  model = gtk_combo_box_get_model (GTK_COMBO_BOX(widget));
  gtk_tree_model_get (model, &iter,
                      1, &value,
                      -1);

  g_settings_set (self->priv->session_settings, "idle-delay", "u", value);

  set_idle_delay_from_dpms (self, value);
}
