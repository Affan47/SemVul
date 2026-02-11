_cb_up(void *data, void *data2 __UNUSED__)
{
   E_Config_Dialog_Data *cfdata;
   Eina_List *l;
   Evas *evas;
   const char *lbl;
   int sel;

   if (!(cfdata = data)) return;
   evas = evas_object_evas_get(cfdata->o_list);
   evas_event_freeze(evas);
   edje_freeze();
   e_widget_ilist_freeze(cfdata->o_list);

   sel = e_widget_ilist_selected_get(cfdata->o_list);
   lbl = e_widget_ilist_selected_label_get(cfdata->o_list);
   if ((l = eina_list_search_unsorted_list(cfdata->apps, _cb_desks_name, lbl)))
     {
        Efreet_Desktop *desk;
        Evas_Object *icon = NULL;

        desk = eina_list_data_get(l);
        if (l->prev)
          {
             Eina_List *ll;

             ll = l->prev;
             cfdata->apps = eina_list_remove_list(cfdata->apps, l);
             cfdata->apps = eina_list_prepend_relative_list(cfdata->apps, desk, ll);

             e_widget_ilist_remove_num(cfdata->o_list, sel);
             e_widget_ilist_go(cfdata->o_list);
             icon = e_util_desktop_icon_add(desk, 24, evas);
             e_widget_ilist_prepend_relative(cfdata->o_list, icon, desk->name,
                                             _cb_order_list_selected, cfdata,
                                             NULL, (sel - 1));
             e_widget_ilist_selected_set(cfdata->o_list, (sel - 1));
          }
     }

   e_widget_ilist_go(cfdata->o_list);
   e_widget_ilist_thaw(cfdata->o_list);
   edje_thaw();
   evas_event_thaw(evas);
}
