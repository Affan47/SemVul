get_prid_from_path (const char *path)
{
  if (strchr (path, '/') == NULL)
    {
      return (path);
    }
  return (strrchr (path, '/') + 1);
}
