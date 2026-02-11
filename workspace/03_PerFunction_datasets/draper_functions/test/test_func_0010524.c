_open_test_cb(void *file)
{
   if (!edje_file_group_exists(eet_file_get(file), "e/desktop/background"))
     e_util_dialog_show(_("Theme File Error"),
                        _("%s is probably not an E17 theme!"),
                        eet_file_get(file));
}
