efreet_icon_shutdown(void)
{
    IF_RELEASE(efreet_icon_user_dir);
    IF_RELEASE(efreet_icon_deprecated_user_dir);

    IF_FREE_LIST(efreet_icon_extensions, eina_stringshare_del);
    efreet_extra_icon_dirs = eina_list_free(efreet_extra_icon_dirs);

    eina_log_domain_unregister(_efreet_icon_log_dom);
    _efreet_icon_log_dom = -1;
    IF_FREE_HASH(change_monitors);
}
