e_desklock_hide(void)
{
   E_Desklock_Popup_Data *edp;
   E_Event_Desklock *ev;

   if ((!edd) && (!_e_custom_desklock_exe)) return;

   if (e_config->desklock_language)
     e_intl_language_set(e_config->language);

   if (e_config_xkb_layout_eq(e_config->xkb.current_layout, e_config->xkb.lock_layout))
     {
        if (e_config->xkb.sel_layout)
          e_xkb_layout_set(e_config->xkb.sel_layout);
     }

   _e_desklock_state = EINA_FALSE;
   ev = E_NEW(E_Event_Desklock, 1);
   ev->on = 0;
   ev->suspend = 1;
   ecore_event_add(E_EVENT_DESKLOCK, ev, NULL, NULL);

   if (e_config->desklock_use_custom_desklock)
     {
        _e_custom_desklock_exe = NULL;
        return;
     }

   if (!edd) return;
   if (edd->elock_grab_break_wnd)
     ecore_x_window_show(edd->elock_grab_break_wnd);

   EINA_LIST_FREE(edd->elock_wnd_list, edp)
     _e_desklock_popup_free(edp);

   E_FREE_LIST(edd->handlers, ecore_event_handler_del);
   if (edd->move_handler) ecore_event_handler_del(edd->move_handler);

   e_grabinput_release(edd->elock_wnd, edd->elock_wnd);
   ecore_x_window_free(edd->elock_wnd);

   E_FREE(edd);
   edd = NULL;

   if (_e_desklock_autolock_time > 0.0)
     {
        if ((e_config->desklock_ask_presentation) &&
            (e_config->desklock_ask_presentation_timeout > 0.0))
          {
             double max, now;

             now = ecore_loop_time_get();
             max = _e_desklock_autolock_time + e_config->desklock_ask_presentation_timeout;
             if (now <= max)
               _e_desklock_ask_presentation_mode();
          }
        else
          _e_desklock_ask_presentation_count = 0;

        _e_desklock_autolock_time = 0.0;
     }
   e_util_env_set("E_DESKLOCK_LOCKED", "freefreefree");
}
