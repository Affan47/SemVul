_ibar_go_focus(void)
{
   E_Manager *man;
   IBar *b;

   if (_ibar_focus_win) return;
   man = e_manager_current_get();
   if (!man) return;
   _ibar_focus_win = ecore_x_window_input_new(man->root, -10, -20, 1, 1);
   ecore_x_window_show(_ibar_focus_win);
   if (!e_grabinput_get(0, 0, _ibar_focus_win))
     {
        ecore_x_window_free(_ibar_focus_win);
        _ibar_focus_win = 0;
        return;
     }
   _ibar_key_down_handler = ecore_event_handler_add
     (ECORE_EVENT_KEY_DOWN, _ibar_focus_cb_key_down, NULL);
   if (!_ibar_key_down_handler) goto err;
   b = _ibar_manager_find(man);
   if (!b) goto err;
   _ibar_focus(b);
   return;
err:
   if (_ibar_key_down_handler) ecore_event_handler_del(_ibar_key_down_handler);
   _ibar_key_down_handler = NULL;
   if (_ibar_focus_win)
     {
        e_grabinput_release(0, _ibar_focus_win);
        ecore_x_window_free(_ibar_focus_win);
     }
   _ibar_focus_win = 0;
}
