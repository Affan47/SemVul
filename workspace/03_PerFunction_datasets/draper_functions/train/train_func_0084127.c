arrays_contain_same_windows (Window *a,
                             int     a_len,
                             Window *b,
                             int     b_len)
{
  Window *a_tmp;
  Window *b_tmp;
  gboolean result;

  if (a_len != b_len)
    return FALSE;

  if (a_len == 0)
    return TRUE;

  a_tmp = g_new (Window, a_len);
  b_tmp = g_new (Window, b_len);

  memcpy (a_tmp, a, a_len * sizeof (Window));
  memcpy (b_tmp, b, b_len * sizeof (Window));

  qsort (a_tmp, a_len, sizeof (Window), wincmp);
  qsort (b_tmp, b_len, sizeof (Window), wincmp);

  result = memcmp (a_tmp, b_tmp, sizeof (Window) * a_len) == 0;

  g_free (a_tmp);
  g_free (b_tmp);

  return result;
}
