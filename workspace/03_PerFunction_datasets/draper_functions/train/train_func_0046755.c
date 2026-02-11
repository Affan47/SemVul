_fill_desks(E_Config_Dialog_Data *cfdata)
{
   Evas *evas;
   int mw, x, y;
   int i = 0;

   evas = evas_object_evas_get(cfdata->o_desk_list);
   evas_event_freeze(evas);
   edje_freeze();
   e_widget_ilist_freeze(cfdata->o_desk_list);
   e_widget_ilist_clear(cfdata->o_desk_list);

   for (y = 0; y < e_config->zone_desks_y_count; y++)
     for (x = 0; x < e_config->zone_desks_x_count; x++)
       {
          E_Desk *desk;
          Eina_List *l;
          E_Config_Shelf_Desk *sd;

          desk = e_desk_at_xy_get(cfdata->es->zone, x, y);
          e_widget_ilist_append(cfdata->o_desk_list, NULL, desk->name,
                                NULL, NULL, NULL);
          i++;

          EINA_LIST_FOREACH(cfdata->desk_list, l, sd)
            {
               if ((sd->x != x) || (sd->y != y)) continue;
               e_widget_ilist_multi_select(cfdata->o_desk_list, i);
               break;
            }
       }

   e_widget_size_min_get(cfdata->o_desk_list, &mw, NULL);
   e_widget_size_min_set(cfdata->o_desk_list, mw, 180);

   e_widget_ilist_go(cfdata->o_desk_list);
   e_widget_ilist_thaw(cfdata->o_desk_list);
   edje_thaw();
   evas_event_thaw(evas);
}
