_x11_elm_drag_start(Evas_Object *obj, Elm_Sel_Format format, const char *data, void (*dragdone) (void *data, Evas_Object *), void *donecbdata)
{
   Ecore_X_Window xwin = _x11_elm_widget_xwin_get(obj);
   X11_Cnp_Selection *sel;
   Elm_Sel_Type xdnd = ELM_SEL_TYPE_XDND;
   Ecore_Evas *ee;
   int x, y, x2, y2, x3, y3;
   Evas_Object *icon;
   int w, h;

   _x11_elm_cnp_init();

   cnp_debug("starting drag...\n");

   if (dragwin)
     {
        cnp_debug("another obj is dragging...\n");
        return EINA_FALSE;
     }

   ecore_x_dnd_type_set(xwin, "text/uri-list", EINA_TRUE);
   sel = _x11_selections + ELM_SEL_TYPE_XDND;
   sel->active = EINA_TRUE;
   sel->widget = obj;
   sel->format = format;
   sel->selbuf = data ? strdup(data) : NULL;


   dragdonecb = dragdone;
   dragdonedata = donecbdata;

   ecore_x_dnd_aware_set(xwin, EINA_TRUE);
   ecore_x_dnd_callback_pos_update_set(_x11_drag_move, NULL);
   ecore_x_dnd_begin(xwin, (unsigned char *)&xdnd, sizeof(Elm_Sel_Type));
   evas_object_event_callback_add(obj, EVAS_CALLBACK_MOUSE_UP,
                                  _x11_drag_mouse_up, (void *)(long)xwin);
   handler_status = ecore_event_handler_add(ECORE_X_EVENT_XDND_STATUS,
                                            _x11_dnd_status, NULL);
   dragwin = elm_win_add(NULL, "Elm Drag Object", ELM_WIN_UTILITY);
   elm_win_override_set(dragwin, EINA_TRUE);


   icon = elm_icon_add(dragwin);
   elm_image_file_set(icon, data + 7, NULL);
   elm_win_resize_object_add(dragwin, icon);
   evas_object_size_hint_weight_set(icon, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   evas_object_size_hint_align_set(icon, EVAS_HINT_FILL, EVAS_HINT_FILL);


   ee = ecore_evas_ecore_evas_get(evas_object_evas_get(obj));
   ecore_evas_geometry_get(ee, &x, &y, NULL, NULL);
   evas_object_geometry_get(obj, &x2, &y2, &w, &h);
   x += x2;
   y += y2;
   evas_object_move(dragwin, x, y);
   evas_object_resize(icon, w, h);
   evas_object_resize(dragwin, w, h);

   evas_object_show(icon);
   evas_object_show(dragwin);

   evas_pointer_canvas_xy_get(evas_object_evas_get(obj), &x3, &y3);
   _dragx = x3 - x2;
   _dragy = y3 - y2;

   return EINA_TRUE;
}
