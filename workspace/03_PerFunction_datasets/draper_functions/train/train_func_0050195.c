Text(char *s, Point p, float h, char *f, Vector x, Vector y)
{
  Matrix m;
  Vector z;
  Object o, t, font;


  if (DXLength(x)==0) {
    DXSetError(ERROR_BAD_PARAMETER, "#11822", "direction");
    return ERROR;
  }
  if (DXLength(y)==0) {
    DXSetError(ERROR_BAD_PARAMETER, "#11822", "up");
    return ERROR;
  }


  if (!f)
    f = "variable";
  font = DXGetFont(f, NULL, NULL);
  if (!font)
    goto error;


  x = DXNormalize(x);
  y = DXNormalize(y);
  z = DXNormalize(DXCross(x, y));

  m.A[0][0] = x.x*h;    m.A[0][1] = x.y*h;    m.A[0][2] = x.z*h;
  m.A[1][0] = y.x*h;    m.A[1][1] = y.y*h;    m.A[1][2] = y.z*h;
  m.A[2][0] = z.x*h;    m.A[2][1] = z.y*h;    m.A[2][2] = z.z*h;
  m.b[0] = p.x;         m.b[1] = p.y;         m.b[2] = p.z;


  o = DXGeometricText(s, font, NULL);
  if (!o)
    goto error;
  t = (Object)DXNewXform(o, m);
  if (!t) {
    DXDelete(o);
    goto error;
  }
  if (!DXSetFloatAttribute(t, "fuzz", 1.0))
    goto error;


  DXDelete(font);
  return t;

 error:
  DXDelete(font);
  return NULL;
}
