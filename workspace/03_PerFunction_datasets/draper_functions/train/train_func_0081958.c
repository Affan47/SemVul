elm_menu_item_separator_add(Evas_Object *obj,
                            Elm_Object_Item *parent)
{
   Elm_Menu_Item *subitem;
   Elm_Menu_Item *p_item = (Elm_Menu_Item *)parent;

   ELM_MENU_CHECK(obj) NULL;
   ELM_MENU_DATA_GET(obj, sd);


   if (!sd->items) return NULL;


   if (p_item)
     {
        if (!p_item->submenu.items) return NULL;
        subitem = eina_list_last(p_item->submenu.items)->data;
     }
   else subitem = eina_list_last(sd->items)->data;

   if (subitem->separator) return NULL;

   subitem = elm_widget_item_new(obj, Elm_Menu_Item);
   if (!subitem) return NULL;

   elm_widget_item_del_pre_hook_set(subitem, _item_del_pre_hook);
   elm_widget_item_disable_hook_set(subitem, _item_disable_hook);
   elm_widget_item_text_set_hook_set(subitem, _item_text_set_hook);
   elm_widget_item_text_get_hook_set(subitem, _item_text_get_hook);
   elm_widget_item_content_set_hook_set(subitem, _item_content_set_hook);
   elm_widget_item_content_get_hook_set(subitem, _item_content_get_hook);

   subitem->separator = EINA_TRUE;
   _item_separator_obj_create(subitem);
   if (!p_item)
     {
        elm_box_pack_end(sd->bx, VIEW(subitem));
        sd->items = eina_list_append(sd->items, subitem);
     }
   else
     {
        if (!p_item->submenu.bx) _item_submenu_obj_create(p_item);
        elm_box_pack_end(p_item->submenu.bx, VIEW(subitem));
        p_item->submenu.items = eina_list_append
            (p_item->submenu.items, subitem);
     }

   _sizing_eval(obj);
   return (Elm_Object_Item *)subitem;
}
