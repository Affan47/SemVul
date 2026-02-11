hash_func_from_gtype (GType gtype, GHashFunc *func)
{
  switch (gtype)
    {
    case G_TYPE_CHAR:
    case G_TYPE_UCHAR:
    case G_TYPE_BOOLEAN:
    case G_TYPE_INT:
    case G_TYPE_UINT:
      *func = NULL;
      return TRUE;
    case G_TYPE_STRING:
      *func = g_str_hash;
      return TRUE;
    default:
      if (gtype == DBUS_TYPE_G_OBJECT_PATH)
        {
          *func = g_str_hash;
          return TRUE;
        }
      else if (gtype == DBUS_TYPE_G_SIGNATURE)
        {
          *func = g_str_hash;
          return TRUE;
        }
      return FALSE;
    }
}
