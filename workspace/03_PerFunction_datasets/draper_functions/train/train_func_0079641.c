_elm_config_access_set(Eina_Bool is_access)
{
   is_access = !!is_access;
   if (_elm_config->access_mode == is_access) return;
   _elm_config->access_mode = is_access;
   _elm_win_access(is_access);
}
