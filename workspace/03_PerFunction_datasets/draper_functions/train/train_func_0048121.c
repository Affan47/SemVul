_edit_bt_clicked(void *data, Evas_Object *obj, void *event_info __UNUSED__)
{
   Evas_Object *ck = data;

   if (!elm_clock_edit_get(ck))
     {
        elm_object_text_set(obj, "Done");
        elm_clock_edit_set(ck, EINA_TRUE);
        return;
     }
   elm_object_text_set(obj, "Edit");
   elm_clock_edit_set(ck, EINA_FALSE);
}
