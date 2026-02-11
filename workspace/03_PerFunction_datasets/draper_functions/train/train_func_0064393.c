_e_entry_smart_resize(Evas_Object *object, Evas_Coord w, Evas_Coord h)
{
   E_Entry_Smart_Data *sd;

   if ((!object) || !(sd = evas_object_smart_data_get(object)))
     return;

   evas_object_resize(sd->scroll_object, w, h);

   _entry_recalc_size(object);
}
