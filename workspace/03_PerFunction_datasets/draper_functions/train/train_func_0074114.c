add_file_to_list(const gchar * filename)
{
    if (is_loadable(filename)) {
        list_end = g_list_append(list_end, clean_filename(filename));
        list_length++;

        if (list_length == 1)
            files_list = list_end;
        else
            list_end = list_end->next;

        touch(&timestamp);
        return 1;
    }

    return 0;
}
