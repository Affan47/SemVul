g_udisks_volume_eject_with_operation (GVolume* base, GMountUnmountFlags flags, GMountOperation* mount_operation, GCancellable* cancellable, GAsyncReadyCallback callback, gpointer user_data)
{
    GUDisksVolume* vol = G_UDISKS_VOLUME(base);
    if(vol->drive && g_drive_can_eject(G_DRIVE(vol->drive)))
    {
        EjectData* data = g_slice_new(EjectData);
        data->vol = g_object_ref(vol);
        data->callback = callback;
        data->user_data = user_data;
        g_drive_eject_with_operation(G_DRIVE(vol->drive), flags, mount_operation,
                                     cancellable, on_drive_ejected, data);
    }
}
