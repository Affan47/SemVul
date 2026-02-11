xdg_mime_init(void)
{
    if (xdg_check_time_and_dirs())
    {
        xdg_mime_shutdown();
    }

    if (need_reread)
    {
        global_hash = _xdg_glob_hash_new();
        global_magic = _xdg_mime_magic_new();
        alias_list = _xdg_mime_alias_list_new();
        parent_list = _xdg_mime_parent_list_new();

        xdg_run_command_on_dirs((XdgDirectoryFunc) xdg_mime_init_from_directory,
                                NULL);

        need_reread = FALSE;
    }
}
