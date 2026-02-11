_e_fm2_dnd_drop_all_hide(Evas_Object *obj)
{
   E_Fm2_Smart_Data *sd;

   sd = evas_object_smart_data_get(obj);
   if (!sd) return;
   if (sd->drop_all)
     {
        edje_object_signal_emit(sd->overlay, "e,state,drop,stop", "e");
        sd->drop_all = EINA_FALSE;
     }
}
