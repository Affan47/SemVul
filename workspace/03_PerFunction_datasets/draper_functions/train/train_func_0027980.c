libaudio_rewind(libaudio_prop_t *prop)
{
  libaudio_prop_t *ret;

  if (prop == NULL)
    return;

  if (prop->loader == NULL)
    return;

  ret = prop->loader->rewind(prop);
  if (ret == NULL)
    libaudio_free_prop(prop);
}
