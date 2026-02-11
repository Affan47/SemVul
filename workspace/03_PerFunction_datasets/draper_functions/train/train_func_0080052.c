evas_object_change(Evas_Object *obj)
{
   Eina_List *l;
   Evas_Object *obj2;
   Eina_Bool movch = EINA_FALSE;

   if (obj->layer->evas->nochange) return;
   obj->layer->evas->changed = EINA_TRUE;

   if (obj->changed_move)
     {
        movch = EINA_TRUE;
        obj->changed_move = EINA_FALSE;
     }

   if (obj->changed) return;

   evas_render_object_recalc(obj);

   if (!((movch) && (obj->is_static_clip)))
     {
        EINA_LIST_FOREACH(obj->clip.clipees, l, obj2)
          evas_object_change(obj2);
     }
   EINA_LIST_FOREACH(obj->proxy.proxies, l, obj2)
     {
        evas_object_change(obj2);
     }
   if (obj->smart.parent) evas_object_change(obj->smart.parent);
}
