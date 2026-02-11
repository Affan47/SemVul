list_parse_qt2(GList * list, ListItem * item, gboolean detect_only)
{
    ListItem *newitem;
    gchar *data;
    gsize datalen;
    gchar *p;
    gchar url[1024];
    gchar *ptr;
    gchar *urlptr;
    gboolean added = FALSE;


    if (item->localsize < (256 * 1024)) {
        if (g_file_get_contents(item->local, &data, &datalen, NULL)) {

            p = (gchar *) memmem_compat(data, datalen, "mmdr", 4);
            if (p == NULL) {
                gm_log(TRUE, G_LOG_LEVEL_DEBUG, "unable to find mmdr in %s", item->local);
                return list;
            } else {
                while (p != NULL && !added) {
                    urlptr = (gchar *) memmem_compat(p, datalen - (p - data), "url ", 4);


                    if (urlptr == NULL) {
                        p = NULL;
                    } else {
                        urlptr += strlen("url ");
                        g_strlcpy(url, item->src, 1024);
                        ptr = g_strrstr(url, "/");
                        if (ptr != NULL && g_strrstr(urlptr, "://") == NULL) {
                            ptr++;
                            ptr[0] = (char) NULL;
                            g_strlcat(url, urlptr, 1024);
                        } else {
                            g_strlcpy(url, urlptr, 1024);
                        }

                        if (list_find(list, url) == NULL) {
                            if (!detect_only) {
                                item->play = FALSE;
                                newitem = g_new0(ListItem, 1);
                                g_strlcpy(newitem->src, url, 1024);

                                newitem->play = TRUE;
                                newitem->id = item->id;
                                newitem->controlid = item->controlid;
                                g_strlcpy(newitem->path, item->path, 1024);
                                item->id = -1;
                                list = g_list_append(list, newitem);
                            }
                            added = TRUE;
                        }
                        p = (gchar *) memmem_compat(urlptr, datalen - (urlptr - data), "mmdr", 4);
                    }

                }

            }

        } else {

        }


    } else {


    }

    if (added) {
        item->playlist = TRUE;
    }
    return list;

}
