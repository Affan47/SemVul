_list_item_add(E_Config_Dialog_Data *cfdata, const E_Gadcon_Client_Class *cc)
{
   Evas_Object *icon = NULL, *end;
   const char *lbl = NULL;
   Evas *evas;

   evas = evas_object_evas_get(cfdata->basic.o_list);
   if ((cc->func.is_site) && (!cc->func.is_site(cfdata->site)))
     return;
   if (cc->func.label) lbl = cc->func.label(cc);
   if (!lbl) lbl = cc->name;
   if (cc->func.icon) icon = cc->func.icon(cc, evas);

   end = edje_object_add(evas);
   if (!e_theme_edje_object_set(end, "base/theme/widgets",
                                "e/widgets/ilist/toggle_end"))
     {
        evas_object_del(end);
        end = NULL;
     }

   if (_search_hash(cfdata, cc->name))
     {
        if (end) edje_object_signal_emit(end, "e,state,checked", "e");
     }
   else
     {
        if (end) edje_object_signal_emit(end, "e,state,unchecked", "e");
     }

   e_widget_ilist_append_full(cfdata->basic.o_list, icon, end, lbl,
                              _cb_list_selected, cfdata, cc->name);
}
