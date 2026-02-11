_item_select(Item *it)
{
   it->selected = EINA_TRUE;
   edje_object_signal_emit(it->o_base, "e,state,selected", "e");
   if (it->o_icon)
     {
        if (strcmp(evas_object_type_get(it->o_icon), "e_icon"))
          edje_object_signal_emit(it->o_icon, "e,state,selected", "e");
        else
          e_icon_selected_set(it->o_icon, EINA_TRUE);
     }
   _item_show(it);
   if (it->func) it->func((void *)it->data1, (void *)it->data2);
}
