efreet_icon_size_match(Efreet_Cache_Icon_Element *elem, unsigned int size)
{
    if (elem->type == EFREET_ICON_SIZE_TYPE_FIXED)
        return (elem->normal == size);

    if ((elem->type == EFREET_ICON_SIZE_TYPE_SCALABLE) ||
        (elem->type == EFREET_ICON_SIZE_TYPE_THRESHOLD))
        return ((elem->min < size) && (size < elem->max));

    return 0;
}
