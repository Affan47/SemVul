FirstBlack(striparray *mystripe, long startpos, long deep)
{

  long i;
  boolean columnempty;

  i = startpos;
  columnempty = true;
  while (columnempty && i < strpwide / 8) {
    columnempty = (columnempty && IsColumnEmpty(mystripe, i,deep));
    if (columnempty)
      i++;
  }
  return i;
}
