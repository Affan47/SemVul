qt_connect(lua_State *L)
{


  QObject *obj = luaQ_checkqobject<QObject>(L, 1);
  const char *sig = luaL_checkstring(L, 2);
  QObject *robj = luaQ_toqobject(L, 3);
  if (robj)
    {

      QByteArray rsig = luaL_checkstring(L, 4);
      const QMetaObject *mo = robj->metaObject();
      int idx = mo->indexOfMethod(rsig.constData());
      if (idx < 0)
        {
          rsig = QMetaObject::normalizedSignature(rsig.constData());
          idx = mo->indexOfMethod(rsig.constData());
          if (idx < 0)
            luaL_error(L, "cannot find target slot or signal %s",
                       rsig.constData());
        }

      QMetaMethod method = mo->method(idx);
      if (method.methodType() == QMetaMethod::Signal)
        rsig.prepend('0' + QSIGNAL_CODE);
      else if (method.methodType() == QMetaMethod::Slot)
        rsig.prepend('0' + QSLOT_CODE);
      else
        luaL_error(L, "target %s is not a slot or a signal",
                   rsig.constData());

      QByteArray ssig = sig;
      ssig.prepend('0' + QSIGNAL_CODE);
      if (! QObject::connect(obj, ssig.constData(), robj, rsig.constData()))
        luaL_error(L, "cannot find source signal %s", sig);
    }
  else
    {
      luaL_checktype(L, 3, LUA_TFUNCTION);
      if (! luaQ_connect(L, obj, sig, 3))
        luaL_error(L, "cannot find source signal %s", sig);
    }
  return 0;
}
