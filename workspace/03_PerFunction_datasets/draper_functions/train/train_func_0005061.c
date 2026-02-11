spi_dec_plat_generate_mouse_event (SpiDEController *controller,
                                   gint x,
                                   gint y,
                                   const char *eventName)
{
  SpiDEControllerClass *klass;
  klass = SPI_DEVICE_EVENT_CONTROLLER_GET_CLASS (controller);
  if (klass->plat.generate_mouse_event)
    return klass->plat.generate_mouse_event (controller, x, y, eventName);
}
