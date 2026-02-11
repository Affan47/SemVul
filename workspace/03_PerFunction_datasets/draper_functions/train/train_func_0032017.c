_cb_grab_key_down(void *data,
                  int type __UNUSED__,
                  void *event)
{
   E_Config_Dialog_Data *cfdata;
   Ecore_Event_Key *ev;

   ev = event;
   if (ev->window != grab_win) return ECORE_CALLBACK_PASS_ON;
   if (!(cfdata = data)) return ECORE_CALLBACK_PASS_ON;
   if (!strcmp(ev->keyname, "Escape"))
     {
        Ecore_Event_Handler *hdl;


        EINA_LIST_FREE(grab_hdls, hdl)
          ecore_event_handler_del(hdl);


        e_grabinput_release(grab_win, grab_win);
        ecore_x_window_free(grab_win);
        grab_win = 0;
        e_object_del(E_OBJECT(grab_dlg));
        grab_dlg = NULL;


        e_acpi_events_thaw();
     }
   return ECORE_CALLBACK_PASS_ON;
}
