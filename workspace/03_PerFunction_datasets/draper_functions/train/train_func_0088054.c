fm_thumbnailer_check_update()
{
    gboolean need_reload = FALSE;

    const gchar * const *data_dirs = g_get_system_data_dirs();
    const gchar * const *data_dir;
    for(data_dir = data_dirs; *data_dir; ++data_dir)
    {
        need_reload = check_data_dir(*data_dir);
        if(need_reload)
            break;
    }


    if(FALSE == need_reload)
        need_reload = check_data_dir(g_get_user_data_dir());

    if(need_reload)
    {

        unload_thumbnailers();


        load_thumbnailers();
    }
}
