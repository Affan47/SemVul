flush_events() {
    fs_list *link = g_event_list;
    while (link) {
        fwrite(link->data, 13, 1, g_event_file);
        free(link->data);
        fs_list *temp = link;
        link = link->next;
        free(temp);
    }
    g_event_list = NULL;
    g_event_count = 0;
}
