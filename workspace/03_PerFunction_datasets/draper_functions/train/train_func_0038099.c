predefined_filename_p (tree node)
{
  unsigned ix;
  tree f;

  FOR_EACH_VEC_SAFE_ELT (predefined_filenames, ix, f)
    if (f == node)
      return 1;

  return 0;
}
