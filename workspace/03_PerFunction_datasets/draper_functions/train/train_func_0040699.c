snd_key(int key, int type) {
    struct input_event ev;
    int ret;

    ev.type = EV_KEY;
    ev.code = key;

    switch (type) {
	case KEY:
	    ev.value = 1;
	    break;
	case REL:
	    ev.value = 0;
	    break;
	case REP:
	    ev.value = 2;
	    break;
	default:
	    return EINVAL;
    }

    ret = fwrite(&ev, sizeof(ev), 1, dev);
    if (ret < 1) {
	lprintf("Error: failed to send event to %s: %s", device, strerror(errno));
	return WRITEERR;
    }

    return OK;
}
