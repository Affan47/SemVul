usb_activate(pcap_t* handle)
{
	char 		full_path[USB_LINE_LEN];


	handle->bufsize = handle->snapshot;
	handle->offset = 0;
	handle->linktype = DLT_USB_LINUX;

	handle->inject_op = usb_inject_linux;
	handle->setfilter_op = install_bpf_program;
	handle->setdirection_op = usb_setdirection_linux;
	handle->set_datalink_op = NULL;
	handle->getnonblock_op = pcap_getnonblock_fd;
	handle->setnonblock_op = pcap_setnonblock_fd;


	if (sscanf(handle->opt.source, USB_IFACE"%d", &handle->md.ifindex) != 1)
	{
		snprintf(handle->errbuf, PCAP_ERRBUF_SIZE,
			"Can't get USB bus index from %s", handle->opt.source);
		return PCAP_ERROR;
	}


	snprintf(full_path, USB_LINE_LEN, LINUX_USB_MON_DEV"%d", handle->md.ifindex);
	handle->fd = open(full_path, O_RDONLY, 0);
	if (handle->fd >= 0)
	{
		if (handle->opt.rfmon) {


			close(handle->fd);
			return PCAP_ERROR_RFMON_NOTSUP;
		}


		if (usb_mmap(handle)) {
			handle->linktype = DLT_USB_LINUX_MMAPPED;
			handle->stats_op = usb_stats_linux_bin;
			handle->read_op = usb_read_linux_mmap;
			handle->cleanup_op = usb_cleanup_linux_mmap;
			probe_devices(handle->md.ifindex);


			handle->selectable_fd = handle->fd;
			return 0;
		}


		handle->stats_op = usb_stats_linux_bin;
		handle->read_op = usb_read_linux_bin;
		probe_devices(handle->md.ifindex);
	}
	else {

		snprintf(full_path, USB_LINE_LEN, USB_TEXT_DIR"/%dt", handle->md.ifindex);
		handle->fd = open(full_path, O_RDONLY, 0);
		if (handle->fd < 0)
		{
			if (errno == ENOENT)
			{


				snprintf(full_path, USB_LINE_LEN, USB_TEXT_DIR_OLD"/%dt", handle->md.ifindex);
				handle->fd = open(full_path, O_RDONLY, 0);
			}
			if (handle->fd < 0) {

				snprintf(handle->errbuf, PCAP_ERRBUF_SIZE,
					"Can't open USB bus file %s: %s", full_path, strerror(errno));
				return PCAP_ERROR;
			}
		}

		if (handle->opt.rfmon) {


			close(handle->fd);
			return PCAP_ERROR_RFMON_NOTSUP;
		}

		handle->stats_op = usb_stats_linux;
		handle->read_op = usb_read_linux;
	}


	handle->selectable_fd = handle->fd;


	handle->buffer = malloc(handle->bufsize);
	if (!handle->buffer) {
		snprintf(handle->errbuf, PCAP_ERRBUF_SIZE,
			 "malloc: %s", pcap_strerror(errno));
		close(handle->fd);
		return PCAP_ERROR;
	}
	return 0;
}
