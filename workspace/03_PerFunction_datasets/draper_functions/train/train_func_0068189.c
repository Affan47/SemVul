inf_user_table_check_local_cb(GObject* object,
                              GParamSpec* pspec,
                              gpointer user_data)
{
  InfUserTable* user_table;
  InfUserTablePrivate* priv;
  GSList* item;

  user_table = INF_USER_TABLE(user_data);
  priv = INF_USER_TABLE_PRIVATE(user_table);
  item = g_slist_find(priv->locals, INF_USER(object));

  if(inf_user_table_is_local(INF_USER(object)) && item == NULL)
  {
    g_signal_emit(
      G_OBJECT(user_table),
      user_table_signals[ADD_LOCAL_USER],
      0,
      INF_USER(object)
    );
  }

  if(!inf_user_table_is_local(INF_USER(object)) && item != NULL)
  {
    g_signal_emit(
      G_OBJECT(user_table),
      user_table_signals[REMOVE_LOCAL_USER],
      0,
      INF_USER(object)
    );
  }
}
