isUnknownInputMode (const gchar * modeName)
{
  gboolean status;
  status = !modeName || !strlen(modeName)
    || strcmp (modeName, DefaultUnknownInputModeName) == 0;
  return (status);
}
