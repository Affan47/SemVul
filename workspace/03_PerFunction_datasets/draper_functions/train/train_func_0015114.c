apwal_iconsel_set_modal(apwalapp_t *apwal)
{
  g_assert(apwal != NULL);
  TRACE("%s", "");


  if (GTK_WIDGET_VISIBLE(apwal->window2))
    gtk_widget_hide(apwal->window2);
  gtk_widget_hide(apwal->w2_btn_apply);
  gtk_widget_hide(apwal->w2_btn_close);
  gtk_widget_show(apwal->w2_btn_cancel);
  gtk_widget_show(apwal->w2_btn_ok);
}
