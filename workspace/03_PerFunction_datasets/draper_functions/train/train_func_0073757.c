gtk_pixcomm_freeze(GtkPixcomm *p)
{
  fc_assert_ret(GTK_IS_PIXCOMM(p));

  p->freeze_count++;
}
