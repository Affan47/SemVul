_e_mod_action_winlist_cb_helper(E_Object *obj, const char *params, int modifiers, E_Winlist_Activate_Type type)
{
   E_Zone *zone = NULL;
   E_Winlist_Filter filter = E_WINLIST_FILTER_NONE;
   int direction = 0;
   int udlr = -1;
   Eina_Bool ok = EINA_TRUE;

   if (obj)
     {
        if (obj->type == E_MANAGER_TYPE)
          zone = e_util_zone_current_get((E_Manager *)obj);
        else if (obj->type == E_CONTAINER_TYPE)
          zone = e_util_zone_current_get(((E_Container *)obj)->manager);
        else if (obj->type == E_ZONE_TYPE)
          zone = e_util_zone_current_get(((E_Zone *)obj)->container->manager);
        else
          zone = e_util_zone_current_get(e_manager_current_get());
     }
   if (!zone) zone = e_util_zone_current_get(e_manager_current_get());
   if (!zone) return;
   if (params)
     {
        if (!strcmp(params, "next"))
          direction = 1;
        else if (!strcmp(params, "prev"))
          direction = -1;
        else if (!strcmp(params, "class-next"))
          direction = 1, filter = E_WINLIST_FILTER_CLASS_WINDOWS;
        else if (!strcmp(params, "class-prev"))
          direction = -1, filter = E_WINLIST_FILTER_CLASS_WINDOWS;
        else if (!strcmp(params, "classes-next"))
          direction = 1, filter = E_WINLIST_FILTER_CLASSES;
        else if (!strcmp(params, "classes-prev"))
          direction = -1, filter = E_WINLIST_FILTER_CLASSES;
        else if (!strcmp(params, "up"))
          udlr = 0;
        else if (!strcmp(params, "down"))
          udlr = 1;
        else if (!strcmp(params, "left"))
          udlr = 2;
        else if (!strcmp(params, "right"))
          udlr = 3;
        else return;
     }
   else
     direction = 1;
   if (direction)
     ok = !e_winlist_show(zone, filter);
   if (!ok)
     {
        if (!type) return;
        if (!direction) return;
        e_winlist_modifiers_set(modifiers, type);
        return;
     }
   if (direction == 1)
     e_winlist_next();
   else if (direction == -1)
     e_winlist_prev();
   if (direction) return;
   switch (udlr)
     {
      case 0:
        e_winlist_up(zone);
        break;
      case 1:
        e_winlist_down(zone);
        break;
      case 2:
        e_winlist_left(zone);
        break;
      case 3:
        e_winlist_right(zone);
        break;
     }
}
