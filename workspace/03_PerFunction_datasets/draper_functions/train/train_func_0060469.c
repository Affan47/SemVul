accumulate_list_attributes (gpointer    result,
                            gpointer    user_data)
{
  GList **results = (GList**)user_data;
  g_assert (results);
  *results = g_list_append (*results, g_pkcs11_array_ref (result));
  return TRUE;
}
