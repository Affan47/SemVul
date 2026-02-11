focusblur_param_store (FblurParam  *param)
{
  const gchar* identifier = PLUG_IN_PROC;
  const gsize  size       = sizeof (FblurStoreParam);

  g_assert (param);

  gimp_procedural_db_set_data (identifier, &(param->store), size);
}
