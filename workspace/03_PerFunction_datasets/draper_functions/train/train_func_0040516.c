dvdrw_device_open_device(Device *dself, char *device_name, char *device_type, char *device_node)
{
    DvdRwDevice *self = DVDRW_DEVICE(dself);
    DeviceClass *parent_class = DEVICE_CLASS(g_type_class_peek_parent(DVDRW_DEVICE_GET_CLASS(dself)));
    GValue val;
    char *colon;

    g_debug("Opening device: %s", device_node);

    bzero(&val, sizeof(val));

    colon = index(device_node, ':');
    if (!colon) {
	device_set_error(dself,
	    stralloc(_("DVDRW device requires cache directory and DVD-RW device separated by a colon (:) in tapedev")),
	    DEVICE_STATUS_DEVICE_ERROR);
	return;
    }

    self->cache_dir = g_strndup(device_node, colon - device_node);
    self->cache_data = g_strconcat(self->cache_dir, "/data/", NULL);
    self->dvdrw_device = g_strdup(colon + 1);

    parent_class->open_device(dself, device_name, device_type, device_node);
}
