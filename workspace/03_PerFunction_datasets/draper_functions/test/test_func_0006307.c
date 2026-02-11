rsvg_property_bag_new (const char **atts)
{
    RsvgPropertyBag *bag;
    int i;

    bag = g_hash_table_new (g_str_hash, g_str_equal);

    if (atts != NULL) {
        for (i = 0; atts[i] != NULL; i += 2)
            g_hash_table_insert (bag, (gpointer) atts[i], (gpointer) atts[i + 1]);
    }

    return bag;
}
