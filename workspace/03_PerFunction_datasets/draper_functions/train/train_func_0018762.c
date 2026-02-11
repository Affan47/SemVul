mxf_uuid_array_parse (MXFUUID ** array, guint32 * count, const guint8 * data,
    guint size)
{
  guint32 element_count, element_size;
  guint i;

  g_return_val_if_fail (array != NULL, FALSE);
  g_return_val_if_fail (count != NULL, FALSE);
  g_return_val_if_fail (data != NULL, FALSE);

  if (size < 8)
    return FALSE;

  element_count = GST_READ_UINT32_BE (data);
  data += 4;
  size -= 4;

  if (element_count == 0) {
    *array = NULL;
    *count = 0;
    return TRUE;
  }

  element_size = GST_READ_UINT32_BE (data);
  data += 4;
  size -= 4;

  if (element_size != 16) {
    *array = NULL;
    *count = 0;
    return FALSE;
  }

  if (16 * element_count < size) {
    *array = NULL;
    *count = 0;
    return FALSE;
  }

  *array = g_new (MXFUUID, element_count);
  *count = element_count;

  for (i = 0; i < element_count; i++) {
    memcpy (&((*array)[i]), data, 16);
    data += 16;
  }

  return TRUE;
}
