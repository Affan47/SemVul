run_new(void)
{
  struct run *tmp;
  if ((tmp = malloc(sizeof(struct run))) == NULL) {
    event_warn("%s: malloc", __func__);
    return (NULL);
  }
  tmp->base = &__run_base;

  tmp->how_data = NULL;
  tmp->how_set = 0;

  tmp->some_bytes_data = NULL;
  tmp->some_bytes_length = 0;
  tmp->some_bytes_set = 0;

  memset(tmp->fixed_bytes_data, 0, sizeof(tmp->fixed_bytes_data));
  tmp->fixed_bytes_set = 0;

  return (tmp);
}
