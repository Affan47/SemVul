has_dependency (GrlMedia *media, GrlKeyID dependency, GList **missing_keys)
{
  if (media && grl_data_has_key (GRL_DATA (media), dependency))
    return TRUE;

  if (missing_keys)
    *missing_keys = grl_metadata_key_list_new (dependency,
                                               NULL);
  return FALSE;
}
