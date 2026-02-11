e_entry_edit(Evas_Object *entry)
{
   E_Entry_Smart_Data *sd;

   if (evas_object_smart_smart_get(entry) != _e_entry_smart) SMARTERRNR();
   if ((!entry) || (!(sd = evas_object_smart_data_get(entry))))
     return;
   if (!sd->noedit)
     return;

   sd->noedit = EINA_FALSE;
   edje_object_signal_emit(e_scrollframe_edje_object_get(sd->scroll_object),
         "e,state,edit", "e");
   edje_object_signal_emit(sd->entry_object, "e,state,edit", "e");
   if (sd->focused)
     {
        edje_object_signal_emit(sd->entry_object, "e,action,show,cursor", "e");
        evas_object_focus_set(sd->entry_object, EINA_TRUE);
     }
}
