LoadNumber (ZIO* Z, int native)
{
 real x;
 if (native)
 {
  LoadBlock(&x,sizeof(x),Z);
  return x;
 }
 else
 {
  char b[256];
  int size=ezgetc(Z);
  LoadBlock(b,size,Z);
  b[size]=0;
  return luaU_str2d(b,zname(Z));
 }
}
