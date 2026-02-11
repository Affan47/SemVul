e_shelf_config_new(E_Zone *zone, E_Config_Shelf *cf_es)
{
   E_Shelf *es;
   Eina_Bool can_show = EINA_FALSE;

   es = e_shelf_zone_new(zone, cf_es->name, cf_es->style,
                         cf_es->popup, cf_es->layer, cf_es->id);
   if (!es) return NULL;

   if (!cf_es->hide_timeout) cf_es->hide_timeout = 1.0;
   if (!cf_es->hide_duration) cf_es->hide_duration = 1.0;
   es->cfg = cf_es;
   es->fit_along = cf_es->fit_along;
   es->fit_size = cf_es->fit_size;

   e_shelf_autohide_set(es, cf_es->autohide + (cf_es->autohide * cf_es->autohide_show_action));
   e_shelf_orient(es, cf_es->orient);
   e_shelf_position_calc(es);
   e_shelf_populate(es);

   if (cf_es->desk_show_mode)
     {
        E_Desk *desk;
        Eina_List *ll;
        E_Config_Shelf_Desk *sd;

        desk = e_desk_current_get(zone);
        EINA_LIST_FOREACH(cf_es->desk_list, ll, sd)
          {
             if ((desk->x == sd->x) && (desk->y == sd->y))
               {
                  can_show = EINA_TRUE;
                  break;
               }
          }
     }
   else
     can_show = EINA_TRUE;

   if (can_show)
     {


        if ((es->gadcon->populated_classes && es->gadcon->clients) || (!es->gadcon->cf->clients))
          if (e_shelf_desk_visible(es, NULL)) e_shelf_show(es);
     }

   e_shelf_toggle(es, 0);
   return es;
}
