sort_by_location (gconstpointer a, gconstpointer b)
{
    guint aloc, bloc;

    g_assert (SEAHORSE_IS_OBJECT (a));
    g_assert (SEAHORSE_IS_OBJECT (b));

    aloc = seahorse_object_get_location (SEAHORSE_OBJECT (a));
    bloc = seahorse_object_get_location (SEAHORSE_OBJECT (b));

    if (aloc == bloc)
        return 0;
    return aloc > bloc ? -1 : 1;
}
