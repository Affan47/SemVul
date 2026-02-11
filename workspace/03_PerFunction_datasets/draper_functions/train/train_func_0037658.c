topo_cairo_write(void *closure, const unsigned char *data, unsigned int length)
{
  if (fwrite(data, length, 1, closure) < 1)
    return CAIRO_STATUS_WRITE_ERROR;
  return CAIRO_STATUS_SUCCESS;
}
