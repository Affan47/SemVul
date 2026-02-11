log_printhex (const char *text, const void *buffer, size_t length)
{
  if (text && *text)
    log_debug ("%s ", text);
  if (length)
    {
      const unsigned char *p = buffer;
      log_printf ("%02X", *p);
      for (length--, p++; length--; p++)
        log_printf (" %02X", *p);
    }
  if (text)
    log_printf ("\n");
}
