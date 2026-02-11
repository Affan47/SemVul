_item_select(Elm_Toolbar_Item *it)
{
   Elm_Toolbar_Item *it2;
   Widget_Data *wd = elm_widget_data_get(WIDGET(it));
   Evas_Object *obj2;
   Eina_Bool sel;
   Evas_Coord w = 0, h = 0;

   if (!wd) return;
   if (elm_widget_item_disabled_get(it) || (it->separator) || (it->object)) return;
   sel = it->selected;

   if (it->object) evas_object_geometry_get(it->object, NULL, NULL, &w, &h);

   if (wd->select_mode != ELM_OBJECT_SELECT_MODE_NONE)
     {
        if (sel)
          {
             if (wd->shrink_mode == ELM_TOOLBAR_SHRINK_EXPAND)
               {
                  if (wd->more_item == it)
                    {
                       edje_object_signal_emit(elm_layout_edje_get(wd->more), "elm,state,close", "elm");
                       _item_unselect(it);
                    }
               }
             if (wd->select_mode != ELM_OBJECT_SELECT_MODE_ALWAYS)
               _item_unselect(it);
          }
        else
          {
             it2 = (Elm_Toolbar_Item *)
                elm_toolbar_selected_item_get(WIDGET(it));
             _item_unselect(it2);

             it->selected = EINA_TRUE;
             wd->selected_item = it;
             if (wd->shrink_mode == ELM_TOOLBAR_SHRINK_EXPAND)
               {
                  if (wd->more_item == it)
                    {
                       if (!evas_object_box_children_get(wd->bx_more2))
                         edje_object_signal_emit(elm_layout_edje_get(wd->more), "elm,state,open", "elm");
                       else
                         edje_object_signal_emit(elm_layout_edje_get(wd->more), "elm,state,open2", "elm");
                    }
                  else
                    {
                       if (it->in_box != wd->bx)
                         {
                            edje_object_signal_emit(wd->VIEW(more_item), "elm,state,selected", "elm");
                            elm_widget_signal_emit(wd->more_item->icon, "elm,state,selected", "elm");
                         }
                       else
                         {
                            edje_object_signal_emit(wd->VIEW(more_item), "elm,state,unselected", "elm");
                            elm_widget_signal_emit(wd->more_item->icon, "elm,state,unselected", "elm");
                         }
                       edje_object_signal_emit(elm_layout_edje_get(wd->more), "elm,state,close", "elm");
                    }
               }
             edje_object_signal_emit(VIEW(it), "elm,state,selected", "elm");
             elm_widget_signal_emit(it->icon, "elm,state,selected", "elm");
             _item_show(it);
          }
     }
   obj2 = WIDGET(it);
   if (it->menu && (!sel))
     {
        evas_object_show(it->o_menu);
        evas_object_event_callback_add(VIEW(it), EVAS_CALLBACK_RESIZE,
                                       _menu_move_resize, it);
        evas_object_event_callback_add(VIEW(it), EVAS_CALLBACK_MOVE,
                                       _menu_move_resize, it);

        _menu_move_resize(it, NULL, NULL, NULL);
     }
   if ((!sel) || (wd->select_mode == ELM_OBJECT_SELECT_MODE_ALWAYS))
     {
        if (it->func) it->func((void *)(it->base.data), WIDGET(it), it);
     }
   evas_object_smart_callback_call(obj2, SIG_CLICKED, it);
}
