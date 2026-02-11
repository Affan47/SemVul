Source(const Proto* f)
{
 const char* s=getstr(f->source);
 if (*s=='@' || *s=='=')
  return s+1;
 else if (*s==LUA_SIGNATURE[0])
  return "(bstring)";
 else
  return "(string)";
}
