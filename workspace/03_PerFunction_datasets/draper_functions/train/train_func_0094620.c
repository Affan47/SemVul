spi_device_event_controller_class_init (SpiDEControllerClass *klass)
{
  GObjectClass * object_class = (GObjectClass *) klass;

  spi_device_event_controller_parent_class = g_type_class_peek_parent (klass);

  object_class->finalize = spi_device_event_controller_object_finalize;

#ifdef HAVE_X11
  if (g_getenv ("DISPLAY"))
    spi_dec_setup_x11 (klass);
  else
#endif
  g_type_class_add_private (object_class, sizeof (long));
}
