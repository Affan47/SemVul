_e_smart_add(Evas_Object *obj)
{
   E_Smart_Data *sd;
   Evas *evas;


   if (!(sd = E_NEW(E_Smart_Data, 1))) return;


   evas = evas_object_evas_get(obj);


   sd->o_layout = e_layout_add(evas);


   sd->o_scroll = e_scrollframe_add(evas);
   e_scrollframe_child_set(sd->o_scroll, sd->o_layout);
   evas_object_smart_member_add(sd->o_scroll, obj);


   evas_object_smart_data_set(obj, sd);
}
