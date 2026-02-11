_elm_config_profile_set(const char *profile)
{
   Eina_Bool changed = EINA_FALSE;

   if (_elm_profile)
     {
        if (strcmp(_elm_profile, profile))
          changed = 1;
        free(_elm_profile);
     }

   _elm_profile = strdup(profile);

   if (changed)
     {
        _config_free();
        _config_load();
        _config_apply();
        _elm_config_font_overlay_apply();
        _elm_rescale();
        _elm_recache();
     }
}
