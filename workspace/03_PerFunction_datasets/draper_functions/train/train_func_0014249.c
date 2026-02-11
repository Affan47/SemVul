sort_objects_by_source (SeahorseObject *k1, SeahorseObject *k2)
{
    SeahorseSource *sk1, *sk2;

    g_assert (SEAHORSE_IS_OBJECT (k1));
    g_assert (SEAHORSE_IS_OBJECT (k2));

    sk1 = seahorse_object_get_source (k1);
    sk2 = seahorse_object_get_source (k2);

    if (sk1 == sk2)
        return 0;

    return sk1 < sk2 ? -1 : 1;
}
