_e_int_menus_shelves_pre_cb(void *data __UNUSED__, E_Menu *m)
{
   E_Menu_Item *mi;
   Eina_List *l, *shelves = NULL;
   E_Shelf *es;
   E_Container *con;
   E_Zone *zone;

   e_menu_pre_activate_callback_set(m, NULL, NULL);
   con = e_container_current_get(e_manager_current_get());
   zone = e_zone_current_get(con);


   shelves = e_shelf_list();
   EINA_LIST_FOREACH(shelves, l, es)
     {
        char buf[1024];
        const char *name;

        if (!es) continue;
        if (es->zone->num != zone->num) continue;
        if (es->cfg->container != (int)con->num) continue;

        if (es->name)
          name = es->name;
        else
          {
             name = buf;
             snprintf(buf, sizeof(buf), _("Shelf %s"), e_shelf_orient_string_get(es));
          }

        mi = e_menu_item_new(m);
        e_menu_item_label_set(mi, name);
        e_menu_item_callback_set(mi, _e_int_menus_shelves_item_cb, es);
        switch (es->cfg->orient)
          {
           case E_GADCON_ORIENT_LEFT:
             e_util_menu_item_theme_icon_set(mi, "preferences-position-left");
             break;

           case E_GADCON_ORIENT_RIGHT:
             e_util_menu_item_theme_icon_set(mi, "preferences-position-right");
             break;

           case E_GADCON_ORIENT_TOP:
             e_util_menu_item_theme_icon_set(mi, "preferences-position-top");
             break;

           case E_GADCON_ORIENT_BOTTOM:
             e_util_menu_item_theme_icon_set(mi, "preferences-position-bottom");
             break;

           case E_GADCON_ORIENT_CORNER_TL:
             e_util_menu_item_theme_icon_set(mi, "preferences-position-top-left");
             break;

           case E_GADCON_ORIENT_CORNER_TR:
             e_util_menu_item_theme_icon_set(mi, "preferences-position-top-right");
             break;

           case E_GADCON_ORIENT_CORNER_BL:
             e_util_menu_item_theme_icon_set(mi, "preferences-position-bottom-left");
             break;

           case E_GADCON_ORIENT_CORNER_BR:
             e_util_menu_item_theme_icon_set(mi, "preferences-position-bottom-right");
             break;

           case E_GADCON_ORIENT_CORNER_LT:
             e_util_menu_item_theme_icon_set(mi, "preferences-position-left-top");
             break;

           case E_GADCON_ORIENT_CORNER_RT:
             e_util_menu_item_theme_icon_set(mi, "preferences-position-right-top");
             break;

           case E_GADCON_ORIENT_CORNER_LB:
             e_util_menu_item_theme_icon_set(mi, "preferences-position-left-bottom");
             break;

           case E_GADCON_ORIENT_CORNER_RB:
             e_util_menu_item_theme_icon_set(mi, "preferences-position-right-bottom");
             break;

           default:
             e_util_menu_item_theme_icon_set(mi, "preferences-desktop-shelf");
             break;
          }
     }
   if (shelves)
     {
        mi = e_menu_item_new(m);
        e_menu_item_separator_set(mi, 1);
     }

   mi = e_menu_item_new(m);
   e_menu_item_label_set(mi, _("Add a Shelf"));
   e_util_menu_item_theme_icon_set(mi, "list-add");
   e_menu_item_callback_set(mi, _e_int_menus_shelves_add_cb, NULL);

   if (shelves)
     {
        mi = e_menu_item_new(m);
        e_menu_item_label_set(mi, _("Delete a Shelf"));
        e_util_menu_item_theme_icon_set(mi, "list-remove");
        e_menu_item_callback_set(mi, _e_int_menus_shelves_del_cb, NULL);
     }
}
