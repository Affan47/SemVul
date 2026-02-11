kkam_iv_popup (ViewerInfo *vi, GdkEventButton *ev)
{
  if (ev->button == 1 || ev->button == 3)
    gtk_menu_popup (GTK_MENU (vi->menu), NULL, NULL, NULL, NULL,
                    ev->button, ev->time);
  return FALSE;
}
