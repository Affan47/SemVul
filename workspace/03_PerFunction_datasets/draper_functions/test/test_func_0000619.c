wap_map_destroy(void)
{
    long i;
    struct url_map_struct *entry;

    if (url_map != NULL) {
        for (i = 0; i < gwlist_len(url_map); i++) {
            entry = gwlist_get(url_map, i);
            octstr_destroy(entry->name);
            octstr_destroy(entry->url);
            octstr_destroy(entry->map_url);
            octstr_destroy(entry->send_msisdn_query);
            octstr_destroy(entry->send_msisdn_header);
            octstr_destroy(entry->send_msisdn_format);
            gw_free(entry);
        }
        gwlist_destroy(url_map, NULL);
    }
    url_map = NULL;
}
