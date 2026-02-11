i64c (int i)
{
  const char *base64 =
    "./01234567890ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
  if (i < 0)
    i = 0;
  else if (i > 63)
    i = 63;

  return base64[i];
}
