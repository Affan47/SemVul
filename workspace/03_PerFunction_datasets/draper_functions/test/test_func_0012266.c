ltype_from_gtype (gint gtype)
{
  gint ltype;


  if (gtype == FC || gtype == FR)
    ltype = SOLID;
  else if (gtype == OC || gtype == OR)
    ltype = WIDE_DASH;
  else
    ltype = NARROW_DASH;

  return ltype;
}
