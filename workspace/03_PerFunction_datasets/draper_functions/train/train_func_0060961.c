luaU_undump (lua_State* L, ZIO* Z)
{
 Proto* tf=NULL;
 int c=zgetc(Z);
 if (c==ID_CHUNK)
  tf=LoadChunk(L,Z);
 c=zgetc(Z);
 if (c!=EOZ)
  luaO_verror(L,"`%.99s' apparently contains more than one chunk",ZNAME(Z));
 return tf;
}
