unix_mkfifo(value path, value mode)
{
  if (mkfifo(String_val(path), Int_val(mode)) == -1)
    uerror("mkfifo", path);
  return Val_unit;
}
