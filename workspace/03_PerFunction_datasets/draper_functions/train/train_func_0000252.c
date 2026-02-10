lua_copytagmethods (int tagto, int tagfrom)
{
  int e;
  checktag(tagto);
  checktag(tagfrom);
  for (e=0; e<IM_N; e++) {
    if (validevent(tagto, e))
      *luaT_getim(tagto, e) = *luaT_getim(tagfrom, e);
  }
  return tagto;
}
