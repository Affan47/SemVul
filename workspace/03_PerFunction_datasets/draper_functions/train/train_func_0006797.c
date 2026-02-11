on_places_computer_changed(FmConfig* cfg, gpointer user_data)
{
    GtkListStore* model = GTK_LIST_STORE(user_data);
    GtkTreeIter it;
    if(cfg->places_computer)
    {
        FmPath* path = fm_path_new_for_uri("computer:///");

        new_path_item(model, &it, path, FM_PLACES_ID_COMPUTER,
                      _("Devices"), "computer", NULL);
        fm_path_unref(path);
    }
    else
    {
        remove_path_item(model, FM_PLACES_ID_COMPUTER);
    }
}
