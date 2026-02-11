open_dev() {
    dev = fopen(device, "r");
    if (dev == NULL) {
	lprintf("Error: could not open %s: %s\n", device, strerror(errno));
	return DEVFAIL;
    }
    return OK;
}
