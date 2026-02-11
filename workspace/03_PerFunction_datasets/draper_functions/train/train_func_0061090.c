qtluapainter_stringrect(lua_State *L)
{
  QtLuaPainter *p = luaQ_checkqobject<QtLuaPainter>(L, 1);
  QString s =luaQ_checkqvariant<QString>(L, 2);
  if (lua_gettop(L) == 2)
    {
      luaQ_pushqt(L, qVariantFromValue(p->stringrect(s)));
    }
  else
    {
      qreal x = luaL_checknumber(L, 3);
      qreal y = luaL_checknumber(L, 4);
      qreal w = luaL_checknumber(L, 5);
      qreal h = luaL_checknumber(L, 6);
      const char *sf = luaL_optstring(L, 7, "");
      const QMetaObject *mo = &QtLuaPainter::staticMetaObject;
      QMetaEnum e = f_enumerator("TextFlags", mo);
      int f = e.keysToValue(sf);
      luaL_argcheck(L, f>=0, 7, "unrecognized flag");
      luaQ_pushqt(L, qVariantFromValue(p->stringrect(s,x,y,w,h,f)));
    }
  return 1;
}
