e_gadcon_layout_unpack(Evas_Object *obj)
{
   E_Gadcon_Layout_Item *bi;
   E_Smart_Data *sd;

   if (!obj) return;
   bi = evas_object_data_get(obj, "e_gadcon_layout_data");
   if (!bi) return;
   sd = bi->sd;
   if (!sd) return;
   sd->items = eina_list_remove(sd->items, obj);
   _e_gadcon_layout_smart_disown(obj);
   _e_gadcon_layout_smart_reconfigure(sd);
}
