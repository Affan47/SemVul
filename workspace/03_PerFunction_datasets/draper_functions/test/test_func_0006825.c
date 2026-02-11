seahorse_service_keyset_match_keys (SeahorseServiceKeyset *keyset, gchar **patterns,
                                    gint flags, gchar ***keys, gchar***unmatched,
                                    GError **error)
{
    GArray *results = NULL;
    GArray *remaining = NULL;
    GList *lkeys, *l;
    SeahorseObject *object;
    const gchar *value;
    gchar *id;
    gchar **k;
    int i;


    remaining = g_array_new (TRUE, TRUE, sizeof (gchar*));
    for(k = patterns; *k; k++) {
        value = g_utf8_casefold (*k, -1);
        g_array_append_val (remaining, value);
    }

    results = g_array_new (TRUE, TRUE, sizeof (gchar*));


    lkeys = seahorse_context_find_objects (SCTX_APP (), keyset->ktype, SEAHORSE_USAGE_NONE,
                                           (flags & MATCH_KEYS_LOCAL_ONLY) ? SEAHORSE_LOCATION_LOCAL : SEAHORSE_LOCATION_INVALID);
    for (l = lkeys; l; l = g_list_next(l)) {

        if (remaining->len <= 0)
            break;

        if (!SEAHORSE_IS_OBJECT (l->data))
            continue;
        object = SEAHORSE_OBJECT (l->data);


        value = seahorse_object_get_label (object);
        if (match_remove_patterns (remaining, value)) {
            id = seahorse_context_object_to_dbus (SCTX_APP (), object);
            g_array_append_val (results, id);
        }


        value = seahorse_object_get_identifier (object);
        if (match_remove_patterns (remaining, value)) {
            id = seahorse_context_object_to_dbus (SCTX_APP (), object);
            g_array_append_val (results, id);
        }
    }


    g_array_sort (results, (GCompareFunc)g_utf8_collate);
    for (i = 0; i < results->len; i++) {
        if (i > 0 && i < results->len) {
            if (strcmp (g_array_index (results, gchar*, i),
                        g_array_index (results, gchar*, i - 1)) == 0) {
                g_free (g_array_index (results, gchar*, i));
                g_array_remove_index (results, i);
                i--;
            }
        }
    }

    *keys = (gchar**)g_array_free (results, FALSE);
    *unmatched = (gchar**)g_array_free (remaining, FALSE);

    return TRUE;
}
