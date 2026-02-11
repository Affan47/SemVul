ezgetc (ZIO* Z)
{
 int c=zgetc(Z);
 if (c==EOZ) unexpectedEOZ(Z);
 return c;
}
