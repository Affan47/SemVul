eio_associate_malloc(const void *data, Eina_Free_Cb free_cb)
{
  Eio_File_Associate *tmp;

  tmp = _eio_pool_malloc(&associate_pool, sizeof (Eio_File_Associate));
  if (!tmp) return tmp;

  tmp->data = (void*) data;
  tmp->free_cb = free_cb;

  return tmp;
}
