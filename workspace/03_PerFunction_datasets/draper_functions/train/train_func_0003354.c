get_private_data (GObject *gobject)
{
  WnckPagerAccessiblePriv *private_data;

  private_data = g_object_get_qdata (gobject,
                                     quark_private_data);
  if (!private_data)
    {
      private_data = g_new0 (WnckPagerAccessiblePriv, 1);
      g_object_set_qdata (gobject,
                          quark_private_data,
                          private_data);
    }
  return private_data;
}
