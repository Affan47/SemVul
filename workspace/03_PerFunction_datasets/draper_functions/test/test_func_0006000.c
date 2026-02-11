_unpack_all_btn_cb(void *data, Evas_Object *obj __UNUSED__, void *event_info __UNUSED__)
{
   Evas_Object *radio, *rdg;
   Eina_List *rl, *l;
   if (!data) return;

   rdg = evas_object_data_get(data, "radio-group");
   if (!rdg) return;

   _index_clear();
   rl = elm_box_children_get(data);
   EINA_LIST_FOREACH(rl, l, radio)
     {
        if (radio != rdg)
          evas_object_del(radio);
     }
   elm_box_unpack_all(data);
   elm_radio_value_set(rdg, -1);
}
