find_property(BSSessionClient *client, const gchar *name)
{
    GSList *list = client->props;
    SessionProperty *prop;

    for (; list; list = list->next) {
        prop = (SessionProperty *)list->data;
        if (strcmp(prop->prop.name, name) == 0)
            return prop;
    }
    return NULL;
}
