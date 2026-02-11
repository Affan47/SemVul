pod_startup2(unsigned long data)
{
	struct usb_line6_pod *pod = (struct usb_line6_pod *)data;
	struct usb_line6 *line6 = &pod->line6;

	CHECK_STARTUP_PROGRESS(pod->startup_progress, POD_STARTUP_VERSIONREQ);


	line6_version_request_async(line6);
}
