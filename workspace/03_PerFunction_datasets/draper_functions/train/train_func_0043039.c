get_error_buffer(void)
{
  _cups_raster_error_t *buf;


  DEBUG_puts("get_error_buffer()");

  pthread_once(&raster_key_once, raster_init);


  if ((buf = (_cups_raster_error_t *)pthread_getspecific(raster_key))
          == NULL)
  {
    DEBUG_puts("get_error_buffer: allocating memory for thread...");


    buf = calloc(1, sizeof(_cups_raster_error_t));
    pthread_setspecific(raster_key, buf);

    DEBUG_printf(("    buf=%p\n", buf));
  }


  return (buf);
}
