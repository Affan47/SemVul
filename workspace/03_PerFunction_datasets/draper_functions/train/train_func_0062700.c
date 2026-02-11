get_profile(const gchar *name)
{
    GList *entry = NULL;
    MudProfile *profile;

    entry = profile_list;

    for (entry = profile_list; entry != NULL; entry = entry->next)
    {
        profile = MUD_PROFILE(entry->data);

        if (!strcmp(profile->name, name))
            return profile;
    }

    return NULL;
}
