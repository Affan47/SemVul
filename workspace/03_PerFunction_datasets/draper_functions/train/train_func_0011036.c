mg_quads(int nquads, HPoint3 *verts, Point3 *normals, ColorA *colors,
	 int qflags)
{
  int i;
  HPoint3 *v = verts;
  Point3 *n = normals;
  ColorA *c = colors;
  int dn = normals ? 4 : 0;
  int dc = colors ? 4 : 0;

  for (i = 0; i < nquads; i++, v += 4, n += dn, c += dc)
    mgpolygon(4, v, dn, n, dc, c);
}
