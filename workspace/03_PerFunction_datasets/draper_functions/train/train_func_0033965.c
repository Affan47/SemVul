luaS_newlstr (char *str, long l)
{
  int i = (l==0)?0:(unsigned char)str[0];
  return insert_s(str, l, &L->string_root[i%NUM_HASHS]);
}
