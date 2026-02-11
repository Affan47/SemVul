mud_profile_load_profiles ()
{
    GSList *profiles, *entry;
    GConfClient *client;

    g_return_if_fail(profile_list == NULL);

    client = gconf_client_get_default();

    profiles = gconf_client_get_list(client, "/apps/gnome-mud/profiles/list", GCONF_VALUE_STRING, NULL);

    for (entry = profiles; entry != NULL; entry = g_slist_next(entry))
    {
        MudProfile *profile;
        gchar *pname, *epname;

        pname = g_strdup((gchar *) entry->data);
        epname = gconf_escape_key(pname, -1);

        profile = mud_profile_new(pname);

        g_free(epname);
        g_free(pname);
    }

    g_object_unref(client);
}
