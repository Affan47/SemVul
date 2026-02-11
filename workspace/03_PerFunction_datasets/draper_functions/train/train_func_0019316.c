_elm_conformant_smart_parent_set(Evas_Object *obj,
                                 Evas_Object *parent)
{
#ifdef HAVE_ELEMENTARY_X
   Evas_Object *top = elm_widget_top_get(parent);
   Ecore_X_Window xwin = elm_win_xwindow_get(parent);

   if ((xwin) && (!elm_win_inlined_image_object_get(top)))
     {
        ELM_CONFORMANT_DATA_GET(obj, sd);

        sd->prop_hdl = ecore_event_handler_add
            (ECORE_X_EVENT_WINDOW_PROPERTY, _on_prop_change, obj);
        sd->vkb_state = ECORE_X_VIRTUAL_KEYBOARD_STATE_OFF;
     }

#endif
}
