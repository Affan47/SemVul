indi_read_cb (void *fd, void *opaque)
{
	struct indi_t *indi = (struct indi_t *)opaque;
	int i, len;
	char buf[4096];
	char errmsg[1024];
	XMLEle *root;
	struct indi_device_t *idev;
	LilXML *lillp = (LilXML *)indi->xml_parser;

	len = io_indi_sock_read(fd, buf, sizeof(buf));
	if(len > 0) {
		dbg_printf("Received (%d): %s\n", len, buf);
		for(i = 0; i < len; i++) {
			root = readXMLEle(lillp, buf[i], errmsg);
		        if (root) {
				const char *dev = findXMLAttValu (root, "device");
				if (! dev) {
					const char *proptype = tagXMLEle(root);
					if (strncmp(proptype, "message", 7) == 0) {
						indigui_show_message(indi, findXMLAttValu(root, "message"));
					}
					continue;
				}
				idev = indi_new_device(indi, dev);
				indi_handle_message(idev, root);
			}
		}
	}
}
