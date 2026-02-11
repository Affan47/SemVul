_evas_object_table_cache_invalidate(Evas_Object_Table_Data *priv)
{
   priv->hints_changed = 1;
   if (priv->cache)
     {
        _evas_object_table_cache_free(priv->cache);
        priv->cache = NULL;
     }
}
