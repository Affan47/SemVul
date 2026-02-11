wheel_callback(GtkWidget *widget, GdkEventScroll *ev)
{
  if (ev->direction == GDK_SCROLL_UP)
  {
    newnumpanels = MIN (numpanels + 1, MAX_NUMPANELS);
    change_num_panels ();
  }
  else if (ev->direction == GDK_SCROLL_DOWN)
  {
    newnumpanels = MAX (numpanels - 1, MIN_NUMPANELS);
    change_num_panels ();
  }
  return TRUE;
}
