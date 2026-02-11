any_remote_file (const struct File_spec *f, size_t n_files)
{
  size_t i;

  for (i = 0; i < n_files; i++)
    if (0 <= f[i].fd && f[i].remote)
      return true;
  return false;
}
