unix_opendir(value path)
{
  DIR * d;
  value res;
  d = opendir(String_val(path));
  if (d == (DIR *) NULL) uerror("opendir", path);
  res = alloc_small(1, Abstract_tag);
  DIR_Val(res) = d;
  return res;
}
