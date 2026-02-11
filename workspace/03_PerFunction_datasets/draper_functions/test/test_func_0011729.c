_e_sys_cb_logout_wait(void *data __UNUSED__, E_Dialog *dia)
{
   if (_e_sys_logout_timer) ecore_timer_del(_e_sys_logout_timer);
   _e_sys_logout_timer = ecore_timer_add(0.5, _e_sys_cb_logout_timer, NULL);
   _e_sys_logout_begin_time = ecore_time_get();
   e_object_del(E_OBJECT(dia));
   _e_sys_logout_confirm_dialog = NULL;
}
