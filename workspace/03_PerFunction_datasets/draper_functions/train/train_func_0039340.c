sw_service_has_cap (const char **caps, const char *cap)
{
  if (!caps)
    return FALSE;

  while (*caps) {
    if (g_str_equal (*caps, cap))
      return TRUE;
    caps++;
  }

  return FALSE;
}
