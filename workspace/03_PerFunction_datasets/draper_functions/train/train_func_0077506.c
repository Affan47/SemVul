get_feature_object_ids (xmlNode *feature)
{
        xmlNode    *element;
        char       *object_ids = NULL;
        const char *content;

        object_ids = (char *) g_malloc0(1);

        for (element = feature->children; element; element = element->next) {
                gsize new_size;

                if (g_ascii_strcasecmp ((char *) element->name,
                                        "objectIDs") == 0) {
                        content = (const char *) xmlNodeGetContent (element);

                        new_size = strlen (object_ids) + strlen (content) + 1;
                        if (*object_ids)
                                new_size++;

                        object_ids = g_realloc (object_ids, new_size);

                        if (*object_ids)
                                strcat (object_ids, ",");
                        strcat (object_ids, content);
                }
        }

        return object_ids;
}
