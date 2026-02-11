e_object_delfn_clear(E_Object *obj)
{
   E_Object_Delfn *dfn;

   E_OBJECT_CHECK(obj);
   if (obj->walking_list)
     {
        EINA_INLIST_FOREACH(obj->del_fn_list, dfn)
          {
             dfn->delete_me = 1;
          }
        return;
     }
   while (obj->del_fn_list)
     {
        dfn = (E_Object_Delfn *)obj->del_fn_list;
        obj->del_fn_list = eina_inlist_remove(obj->del_fn_list,
                                              EINA_INLIST_GET(dfn));
        free(dfn);
     }
}
