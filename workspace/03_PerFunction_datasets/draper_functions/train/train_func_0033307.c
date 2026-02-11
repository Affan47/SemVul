WriteGuid(gbfile* f, GUID* guid)
{
  int i = 0;
  WriteLong(f, guid->l);
  for (i = 0; i < 3; i++) {
    WriteShort(f, guid->s[i]);
  }
  for (i = 0; i < 6; i++) {
    WriteChar(f, guid->c[i]);
  }
}
