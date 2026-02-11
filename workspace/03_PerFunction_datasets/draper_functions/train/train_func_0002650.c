g_udisks_volume_monitor_finalize(GObject *object)
{
    GUDisksVolumeMonitor *self;

    g_return_if_fail(object != NULL);
    g_return_if_fail(G_IS_UDISKS_VOLUME_MONITOR(object));

    self = G_UDISKS_VOLUME_MONITOR(object);

    if(self->idle_handler)
    {
        GList* l;
        g_source_remove(self->idle_handler);
        for(l = self->queued_events; l; l=l->next)
        {
            QueuedEvent* q = (QueuedEvent*)l->data;
            g_object_unref(q->dev);
            g_slice_free(QueuedEvent, q);
        }
        g_list_free(self->queued_events);
    }

    if(self->udisks_proxy)
    {
        dbus_g_proxy_disconnect_signal(self->udisks_proxy, "DeviceAdded", G_CALLBACK(on_device_added), self);
        dbus_g_proxy_disconnect_signal(self->udisks_proxy, "DeviceRemoved", G_CALLBACK(on_device_removed), self);
        dbus_g_proxy_disconnect_signal(self->udisks_proxy, "DeviceChanged", G_CALLBACK(on_device_changed), self);
        g_object_unref(self->udisks_proxy);
    }

    if(self->devices)
    {
        g_list_foreach(self->devices, (GFunc)g_object_unref, NULL);
        g_list_free(self->devices);
    }

    if(self->drives)
    {
        g_list_foreach(self->drives, (GFunc)g_object_unref, NULL);
        g_list_free(self->drives);
    }

    if(self->volumes)
    {
        g_list_foreach(self->volumes, (GFunc)g_object_unref, NULL);
        g_list_free(self->volumes);
    }

    G_OBJECT_CLASS(g_udisks_volume_monitor_parent_class)->finalize(object);
}
