lk_karma_get_device_settings(int rio, char **properties)
{
    if (properties)
        *properties = NULL;
    return lk_ops->lk_karma_get_device_settings(rio);
}
