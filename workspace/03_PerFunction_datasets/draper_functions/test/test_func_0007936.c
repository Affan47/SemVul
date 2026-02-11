gui_url_remove_links (GSList *links_list, gint *link_index) {

gint i;
gchar *link;
GSList *lnode;

        *link_index = 1;

        if (links_list != NULL) {

            for (i = 0, lnode = links_list; lnode != NULL; lnode = lnode->next, i++) {
                link = g_slist_nth_data (links_list, i);
                if (link != NULL) {
                    g_free (link);
                }
            }

            for (i = 0, lnode = links_list; lnode != NULL; lnode = lnode->next, i++) {
                links_list = g_slist_remove_link (links_list, g_slist_nth(links_list, i));
            }

        }
}
