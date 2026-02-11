on_device_release(const char * device_name)
{
    int i;


    for (i = 0; i < DEVICE_MAX; i++) {
 	if (strcmp(g_reserved_device[i].device_name, device_name) == 0)
	    break;
    }

    if (i < DEVICE_MAX) {
	jack_info("Released audio card %s", device_name);
        rd_release(g_reserved_device[i].reserved_device);
    } else {
	jack_error("Audio card %s not found!!", device_name);
    }

    g_device_count--;
}
