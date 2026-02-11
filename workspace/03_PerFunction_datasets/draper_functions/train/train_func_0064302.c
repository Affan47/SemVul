ng_vid_open_auto(struct ng_vid_driver *drv, char *devpath,
			      int allow_grabber)
{
    void *md, *handle = NULL;
    const char *device = NULL;
    const char *scan_type = "an analog TV";

    *devpath = 0;
    md = discover_media_devices();
    if (!md)
	goto error;


    while (1) {
	device = get_associated_device(md, device, MEDIA_V4L_VIDEO, NULL, NONE);
	if (!device)
	    break;
	snprintf(devpath, PATH_MAX, "/dev/%s", device);
	if (ng_debug)
	    fprintf(stderr,"vid-open-auto: trying: %s... \n", devpath);
	handle = (drv->open)(devpath, CAN_CAPTURE | CAN_TUNE);
	if (handle) {
		fprintf(stderr,"vid-open-auto: using analog TV device %s\n", devpath);
		break;
	}
    }


    if (!handle) {
	if (!allow_grabber)
	    goto error;
	scan_type = "a capture";
	device = NULL;
	while (1) {
	    device = get_associated_device(md, device, MEDIA_V4L_VIDEO, NULL, NONE);
	    if (!device)
		break;
	    snprintf(devpath, PATH_MAX, "/dev/%s", device);
	    if (ng_debug)
		fprintf(stderr,"vid-open-auto: trying: %s... \n", devpath);
	    handle = (drv->open)(devpath, CAN_CAPTURE);
	    if (handle) {
		fprintf(stderr,"vid-open-auto: using grabber/webcam device %s\n", devpath);
		break;
	    }
	}
    }
    free_media_devices(md);

error:
    if (!handle) {
	    fprintf(stderr, "vid-open-auto: failed to open %s device",
		    scan_type);
	    if (*devpath)
		    fprintf(stderr, " at %s\n", devpath);
	    else
		    fprintf(stderr, "\n");

	    return NULL;
    }

    if (handle && ng_debug)
	fprintf(stderr,"vid-open-auto: success, using: %s\n", devpath);

    return handle;
}
