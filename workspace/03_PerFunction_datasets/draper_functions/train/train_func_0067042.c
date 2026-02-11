is_valid_path(CPlugin * instance, const char *message)
{
    gboolean result = FALSE;
    ListItem *item;
    GList *iter;

    if (instance == NULL)
        return result;

    if (g_ascii_strcasecmp(message, instance->path) == 0) {

        result = TRUE;

    } else if (g_ascii_strcasecmp(message, "/DEBUG") == 0) {

        result = TRUE;

    } else {

        if (instance->playlist != NULL) {
            for (iter = instance->playlist; iter != NULL; iter = g_list_next(iter)) {
                item = (ListItem *) iter->data;
                if (item != NULL) {
                    if (g_ascii_strcasecmp(message, item->path) == 0) {
                        result = TRUE;
                    }
                }
            }
        }

    }

    return result;
}
