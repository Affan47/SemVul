_backlight_input_win_del(Instance *inst)
{
   if (!inst->input_win) return;
   e_grabinput_release(0, inst->input_win);
   ecore_x_window_free(inst->input_win);
   inst->input_win = 0;
   ecore_event_handler_del(inst->hand_mouse_down);
   inst->hand_mouse_down = NULL;
   ecore_event_handler_del(inst->hand_key_down);
   inst->hand_key_down = NULL;
}
