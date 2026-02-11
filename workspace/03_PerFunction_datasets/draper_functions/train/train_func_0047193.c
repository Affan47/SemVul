_elm_menu_item_add_helper(Evas_Object *obj,
                          Elm_Menu_Item *parent,
                          Elm_Menu_Item *subitem,
                          Elm_Menu_Smart_Data *sd)
{
   if (parent)
     {
        if (!parent->submenu.bx) _item_submenu_obj_create(parent);
        elm_box_pack_end(parent->submenu.bx, VIEW(subitem));
        parent->submenu.items =
          eina_list_append(parent->submenu.items, subitem);
        subitem->idx = eina_list_count(parent->submenu.items) - 1;
     }
   else
     {
        elm_box_pack_end(sd->bx, VIEW(subitem));
        sd->items = eina_list_append(sd->items, subitem);
        subitem->idx = eina_list_count(sd->items) - 1;
     }

   _sizing_eval(obj);
}
