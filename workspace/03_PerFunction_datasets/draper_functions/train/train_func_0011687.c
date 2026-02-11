getKey ()
{
  if (specialActive)
    return special + 256;
  else
    return key;
}
