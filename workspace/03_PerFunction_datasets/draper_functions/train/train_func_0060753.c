_e_fm2_cb_mouse_down(void *data, Evas *e __UNUSED__, Evas_Object *obj __UNUSED__, void *event_info)
{
   Evas_Event_Mouse_Down *ev;
   E_Fm2_Smart_Data *sd;

   sd = data;
   ev = event_info;
   _e_fm2_typebuf_hide(sd->obj);
   if (ev->button == 1)
     {
        Eina_List *l;
        int multi_sel = 0, range_sel = 0, sel_change = 0;

        if (!sd->config->selection.windows_modifiers)
          {
             if (evas_key_modifier_is_set(ev->modifiers, "Shift"))
               range_sel = 1;
             else if (evas_key_modifier_is_set(ev->modifiers, "Control"))
               multi_sel = 1;
          }
        else
          {
             if (evas_key_modifier_is_set(ev->modifiers, "Control"))
               range_sel = 1;
             else if (evas_key_modifier_is_set(ev->modifiers, "Shift"))
               multi_sel = 1;
          }
        if (sd->config->selection.single)
          {
             multi_sel = 0;
             range_sel = 0;
          }
        if ((!multi_sel) && (!range_sel))
          {
             E_Fm2_Icon *ic;
             EINA_LIST_FOREACH(sd->icons, l, ic)
               {
                  if (ic->selected)
                    {
                       _e_fm2_icon_deselect(ic);
                       sel_change = 1;
                    }
               }
          }
        if (sel_change)
          evas_object_smart_callback_call(sd->obj, "selection_change", NULL);

        if (!(ev->event_flags & EVAS_EVENT_FLAG_ON_HOLD))
          {
             if (!sd->config->selection.single)
               {
                  sd->selrect.ox = ev->canvas.x;
                  sd->selrect.oy = ev->canvas.y;
                  sd->selecting = EINA_TRUE;
               }
          }
        if (ev->flags & EVAS_BUTTON_DOUBLE_CLICK)
          evas_object_smart_callback_call(sd->obj, "double_clicked", NULL);
     }
   else if (ev->button == 3)
     {
        _e_fm2_menu(sd->obj, ev->timestamp);
     }
}
