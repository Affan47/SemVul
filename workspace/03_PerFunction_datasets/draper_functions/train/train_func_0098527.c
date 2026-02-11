_queue_remove(Evas_Object *obj, E_Widget_Queue_Item *qi, int del)
{
   E_Widget_Data *wd;

   wd = e_widget_data_get(obj);
   if (!wd) return;
   wd->queue.queue = eina_list_remove(wd->queue.queue, qi);
   if (del)
     {
        if (qi->icon) evas_object_del(qi->icon);
        if (qi->end) evas_object_del(qi->end);
     }
   eina_stringshare_del(qi->label);
   eina_stringshare_del(qi->val);
   free(qi);
}
