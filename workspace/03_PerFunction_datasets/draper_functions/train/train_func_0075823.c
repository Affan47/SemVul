get_gobj_from_address(gpointer addr)
{
  GObject *obj;

  if (!G_IS_OBJECT(addr))
      return NULL;

  obj = G_OBJECT(addr);

  if (!obj)
      return NULL;

  return pygobject_new(obj);
}
