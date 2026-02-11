evas_object_table_unpack(Evas_Object *o, Evas_Object *child)
{
   Evas_Object_Table_Option *opt;

   EVAS_OBJECT_TABLE_DATA_GET_OR_RETURN_VAL(o, priv, 0);

   if (o != evas_object_smart_parent_get(child))
     {
        ERR("cannot unpack child from incorrect table!");
        return EINA_FALSE;
     }

   opt = _evas_object_table_option_del(child);
   if (!opt)
     {
        ERR("cannot unpack child with no packing option!");
        return EINA_FALSE;
     }

   _evas_object_table_child_disconnect(o, child);
   _evas_object_table_remove_opt(priv, opt);
   evas_object_smart_member_del(child);
   free(opt);
   _evas_object_table_cache_invalidate(priv);
   evas_object_smart_changed(o);

   return EINA_TRUE;
}
