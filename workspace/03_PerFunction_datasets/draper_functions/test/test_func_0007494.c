evas_call_smarts_calculate(Evas *e)
{
   Eina_Clist *elem;
   Evas_Object *obj;


   evas_event_freeze(e);
   e->in_smart_calc++;

   while (NULL != (elem = eina_clist_head(&e->calc_list)))
     {
        Evas_Object_Smart *o;


        obj = EINA_CLIST_ENTRY(elem, Evas_Object, calc_entry);
        eina_clist_remove(&obj->calc_entry);
        if (obj->delete_me) continue;
        eina_clist_add_tail(&e->calc_done, &obj->calc_entry);

        o = obj->object_data;

        if (o->need_recalculate)
          {
             o->need_recalculate = 0;
             obj->smart.smart->smart_class->calculate(obj);
          }
     }

   while (NULL != (elem = eina_clist_head(&e->calc_done)))
     {
        obj = EINA_CLIST_ENTRY(elem, Evas_Object, calc_entry);
        obj->recalculate_cycle = 0;
        eina_clist_remove(&obj->calc_entry);
     }

   e->in_smart_calc--;
   if (e->in_smart_calc == 0) e->smart_calc_count++;
   evas_event_thaw(e);
   evas_event_thaw_eval(e);
}
