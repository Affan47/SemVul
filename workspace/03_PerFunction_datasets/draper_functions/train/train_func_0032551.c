_e_xsettings_done_cb(void *data __UNUSED__, Eio_File *handler __UNUSED__, const Eina_Stat *estat __UNUSED__)
{
   if (reset)
     {

        _e_xsettings_error_cb(NULL, NULL, 0);
        return;
     }
   _e_xsettings_string_set(_setting_theme_name, _setting_theme);
   _setting_theme = NULL;
   eio_op = NULL;
   setting = EINA_FALSE;
   _e_xsettings_update();
   _e_xsettings_gtk_rcfiles_update();
}
