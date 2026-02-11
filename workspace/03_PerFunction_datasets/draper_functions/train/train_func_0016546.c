osinfo_devicelinkfilter_matches_default(OsinfoFilter *filter, OsinfoEntity *entity)
{
    g_return_val_if_fail(OSINFO_IS_DEVICELINKFILTER(filter), FALSE);
    g_return_val_if_fail(OSINFO_IS_DEVICELINK(entity), FALSE);
    OsinfoDeviceLinkFilter *linkfilter = OSINFO_DEVICELINKFILTER(filter);

    if (!OSINFO_FILTER_CLASS (osinfo_devicelinkfilter_parent_class)->matches(filter, entity))
        return FALSE;

    if (!osinfo_filter_matches(linkfilter->priv->targetFilter,
                               OSINFO_ENTITY(osinfo_devicelink_get_target(OSINFO_DEVICELINK(entity)))))
        return FALSE;

    return TRUE;
}
