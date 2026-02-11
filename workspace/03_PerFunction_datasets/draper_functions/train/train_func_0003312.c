efreet_menu_desktop_free(Efreet_Menu_Desktop *md)
{
    IF_RELEASE(md->id);
    if (md->desktop) efreet_desktop_free(md->desktop);
    FREE(md);
}
