elm_grid_clear(Evas_Object *obj,
               Eina_Bool clear)
{
   Eina_List *chld;
   Evas_Object *o;

   ELM_GRID_CHECK(obj);
   ELM_GRID_DATA_GET(obj, sd);

   if (!clear)
     {
        chld = evas_object_grid_children_get(ELM_WIDGET_DATA(sd)->resize_obj);
        EINA_LIST_FREE (chld, o)
          elm_widget_sub_object_del(obj, o);
     }

   evas_object_grid_clear(ELM_WIDGET_DATA(sd)->resize_obj, clear);
}
