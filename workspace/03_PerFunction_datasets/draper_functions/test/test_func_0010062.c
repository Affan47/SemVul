p_orig_labels_update (GtkWidget *widget,
                    gpointer   data)
{
  GapResizePrivateType *res_private;
  gchar          buf[32];


  res_private  = (GapResizePrivateType *) data;

  if(res_private)
  {
    g_snprintf (buf, sizeof (buf), "%d", res_private->orig_width);
    gtk_label_set_text (GTK_LABEL (res_private->orig_width_label), buf);
    g_snprintf (buf, sizeof (buf), "%d", res_private->orig_height);
    gtk_label_set_text (GTK_LABEL (res_private->orig_height_label), buf);
  }
}
