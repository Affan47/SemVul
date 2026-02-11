zaxis2ltype(int zaxisID)
{
  int ltype;
  int zaxistype;

  zaxistype = zaxisInqType(zaxisID);

  ltype = zaxisInqLtype(zaxisID);

  if ( ltype <= 0 ) ltype = ztype2ltype(zaxistype);

  return (ltype);
}
