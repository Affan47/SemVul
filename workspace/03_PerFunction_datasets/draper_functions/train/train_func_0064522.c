libaudio_close(libaudio_prop_t *prop)
{
  if (prop == NULL)
    return;

  if (prop->loader == NULL)
    return;

  prop->loader->close(prop);
  libaudio_free_prop(prop);
}
