g_udisks_drive_eject_with_operation (GDrive* base, GMountUnmountFlags flags, GMountOperation* mount_operation, GCancellable* cancellable, GAsyncReadyCallback callback, gpointer user_data)
{
    GUDisksDrive* drv = G_UDISKS_DRIVE(base);
    GList* vols = g_udisks_drive_get_volumes(base);
    GList* mounts = NULL;
    EjectData* data;


    if(vols)
    {
        GList* l;
        for(l = vols; l; l=l->next)
        {
            GVolume* vol = G_VOLUME(l->data);
            GMount* mnt = g_volume_get_mount(vol);
            if(mnt)
                mounts = g_list_prepend(mounts, mnt);
            g_object_unref(vol);
        }
        g_list_free(vols);
    }

    data = g_slice_new0(EjectData);
    data->drv = g_object_ref(drv);
    data->callback = callback;
    data->cancellable = cancellable ? g_object_ref(cancellable) : NULL;
    data->flags = flags;
    data->op = mount_operation ? g_object_ref(mount_operation) : NULL;
    data->user_data = user_data;

    if(cancellable)
        g_signal_connect(cancellable, "cancelled", G_CALLBACK(on_eject_cancelled), data);

    if(mounts)
    {


        data->mounts = mounts;
        unmount_before_eject(data);
    }
    else
        do_eject(data);
}
