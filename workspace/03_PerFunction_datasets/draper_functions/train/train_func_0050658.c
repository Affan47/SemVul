find_file_in_dir (cpp_reader *pfile, _cpp_file *file, bool *invalid_pch)
{
  char *path;

  if (CPP_OPTION (pfile, remap) && (path = remap_filename (pfile, file)))
    ;
  else
    path = append_file_to_dir (file->name, file->dir);

  file->path = path;
  if (pch_open_file (pfile, file, invalid_pch))
    return true;

  if (open_file (file))
    return true;

  if (file->err_no != ENOENT)
    {
      open_file_failed (pfile, file, 0);
      return true;
    }

  free (path);
  file->path = file->name;
  return false;
}
