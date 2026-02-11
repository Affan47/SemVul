gmpc_plugin_status_changed(gmpcPluginParent * plug, MpdObj * mi,
                                ChangedStatusType what)
{
    if (plug->new)
        return;
    if (plug->old->mpd_status_changed)
    {
        plug->old->mpd_status_changed(mi, what, NULL);
    }
}
