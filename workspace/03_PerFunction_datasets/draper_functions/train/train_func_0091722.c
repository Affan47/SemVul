efreet_icon_lookup_icon(Efreet_Cache_Icon *icon, unsigned int size)
{
    const char *path = NULL;
    double minimal_distance = INT_MAX;
    unsigned int ret_size = 0;
    unsigned int i;

    if (!icon) return NULL;


    for (i = 0; i < icon->icons_count; ++i)
    {
        if (!efreet_icon_size_match(icon->icons[i], size)) continue;
        path = efreet_icon_lookup_path(icon->icons[i]);
        if (path) return path;
    }


    for (i = 0; i < icon->icons_count; ++i)
    {
        const char *tmp = NULL;
        double distance;

        distance = efreet_icon_size_distance(icon->icons[i], size);
        if (distance > minimal_distance) continue;

        if ((distance == minimal_distance) && (icon->icons[i]->normal < ret_size)) continue;

        tmp = efreet_icon_lookup_path(icon->icons[i]);

        if (tmp)
        {
            path = tmp;
            minimal_distance = distance;
            ret_size = icon->icons[i]->normal;
        }
    }

    return path;
}
