mud_profile_from_number(gint num)
{
    GList *entry;
    gint counter = 0;

    for (entry = (GList *)profile_list; entry != NULL; entry = g_list_next(entry))
    {
        if (counter == num)
            return (gchar *)MUD_PROFILE(entry->data)->name;

        counter++;
    }

    return NULL;
}
