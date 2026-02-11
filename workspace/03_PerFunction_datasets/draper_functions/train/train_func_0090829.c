blinky_destroy(GtkObject * object)
{
  Blinky *blinky;

  g_return_if_fail(object != NULL);
  g_return_if_fail(IS_BLINKY(object));

  blinky = BLINKY(object);


  if (GTK_OBJECT_CLASS(blinky_parent_class)->destroy)
    (*GTK_OBJECT_CLASS(blinky_parent_class)->destroy) (object);
}
