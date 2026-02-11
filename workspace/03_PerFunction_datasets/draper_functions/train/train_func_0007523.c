_x11_elm_cnp_selection_set(Evas_Object *obj, Elm_Sel_Type selection, Elm_Sel_Format format, const void *selbuf, size_t buflen)
{
   Ecore_X_Window xwin = _x11_elm_widget_xwin_get(obj);
   X11_Cnp_Selection *sel;

   _x11_elm_cnp_init();
   if ((!selbuf) && (format != ELM_SEL_FORMAT_IMAGE))
     return elm_object_cnp_selection_clear(obj, selection);

   sel = _x11_selections + selection;
   if (sel->loss_cb) sel->loss_cb(sel->loss_data, selection);
   if (sel->widget)
     evas_object_event_callback_del_full(sel->widget, EVAS_CALLBACK_DEL,
                                         _x11_sel_obj_del, sel);
   sel->widget = NULL;

   sel->active = EINA_TRUE;
   sel->widget = obj;
   sel->xwin = xwin;
   sel->set(xwin, &selection, sizeof(Elm_Sel_Type));
   sel->format = format;
   sel->loss_cb = NULL;
   sel->loss_data = NULL;

   evas_object_event_callback_add
     (sel->widget, EVAS_CALLBACK_DEL, _x11_sel_obj_del, sel);

   if (selbuf)
     {
        if (format == ELM_SEL_FORMAT_IMAGE)
          {

             sel->selbuf = malloc(buflen);
             if (!sel->selbuf)
               {
                  elm_object_cnp_selection_clear(obj, selection);
                  return EINA_FALSE;
               }
             memcpy(sel->selbuf, selbuf, buflen);
          }
        else
          sel->selbuf = strdup((char*)selbuf);
     }
   else
     sel->selbuf = NULL;

   return EINA_TRUE;
}
