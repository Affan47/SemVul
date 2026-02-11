gst_plugin_ext_dep_strv_equal (gchar ** arr1, gchar ** arr2)
{
  if (arr1 == arr2)
    return TRUE;
  if (arr1 == NULL || arr2 == NULL)
    return FALSE;
  for (; *arr1 != NULL && *arr2 != NULL; ++arr1, ++arr2) {
    if (strcmp (*arr1, *arr2) != 0)
      return FALSE;
  }
  return (*arr1 == *arr2);
}
