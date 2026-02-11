fm_unmount_volume(GtkWindow* parent, GVolume* vol, gboolean interactive)
{
    GMount* mount = g_volume_get_mount(vol);
    gboolean ret;
    if(!mount)
        return FALSE;
    ret = fm_do_mount(parent, G_OBJECT(vol), UMOUNT_MOUNT, interactive);
    g_object_unref(mount);
    return ret;
}
