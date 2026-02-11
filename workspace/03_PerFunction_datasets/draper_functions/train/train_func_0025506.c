_e_border_action_move_timeout_add(void)
{
   E_FN_DEL(ecore_timer_del, action_timer);
   if (e_config->border_keyboard.timeout)
     action_timer = ecore_timer_add(e_config->border_keyboard.timeout, _e_border_action_move_timeout, NULL);
}
