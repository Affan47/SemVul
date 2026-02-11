null_device_start (Device * pself, DeviceAccessMode mode,
                   char * label, char * timestamp) {
    NullDevice * self;
    self = NULL_DEVICE(pself);

    if (device_in_error(self)) return FALSE;

    pself->access_mode = mode;
    g_mutex_lock(pself->device_mutex);
    pself->in_file = FALSE;
    g_mutex_unlock(pself->device_mutex);

    if (mode == ACCESS_WRITE) {
        pself->volume_label = newstralloc(pself->volume_label, label);
        pself->volume_time = newstralloc(pself->volume_time, timestamp);
	pself->header_block_size = 32768;
	return TRUE;
    } else {
	device_set_error(pself,
	    stralloc(_("Can't open NULL device for reading or appending.")),
	    DEVICE_STATUS_VOLUME_UNLABELED | DEVICE_STATUS_VOLUME_ERROR);
        return FALSE;
    }
}
