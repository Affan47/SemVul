find_device_l(GUDisksVolumeMonitor* mon, const char* obj_path)
{
    GList* l;
    for(l = mon->devices; l; l=l->next)
    {
        GUDisksDevice* dev = G_UDISKS_DEVICE(l->data);
        if(g_strcmp0(dev->obj_path, obj_path) == 0)
            return l;
    }
    return NULL;
}
