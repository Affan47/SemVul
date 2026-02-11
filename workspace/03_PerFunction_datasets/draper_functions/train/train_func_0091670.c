list_initialized(gboolean sort, gboolean shuffle)
{
    if (sort || shuffle)
        reorder_list(shuffle);

    touch(&timestamp);
}
