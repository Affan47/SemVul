iface_setup_binding_from_kern_iface(void *data,
					       struct iface_rec *kern_iface)
{
	struct host_info *hinfo = data;
	struct iface_rec iface;

	if (!strlen(hinfo->iface.hwaddress)) {
		log_error("Invalid offload iSCSI host %u. Missing "
			  "hwaddress. Try upgrading %s driver.\n",
			  hinfo->host_no, hinfo->iface.transport_name);
		return 0;
	}

	memset(&iface, 0, sizeof(struct iface_rec));
	strcpy(iface.hwaddress, hinfo->iface.hwaddress);
	strcpy(iface.transport_name, hinfo->iface.transport_name);

	if (kern_iface) {
		iface.iface_num = kern_iface->iface_num;

		snprintf(iface.name, sizeof(iface.name), "%s.%s.%s.%u",
			 kern_iface->transport_name,
			 kern_iface->hwaddress,
			 iface_get_iptype(kern_iface) == ISCSI_IFACE_TYPE_IPV4 ?
			 "ipv4" : "ipv6", kern_iface->iface_num);
	} else {
		snprintf(iface.name, sizeof(iface.name), "%s.%s",
			 hinfo->iface.transport_name, hinfo->iface.hwaddress);
	}

	if (iface_conf_read(&iface)) {

		if (iface_conf_write(&iface)) {
			log_error("Could not create default iface conf %s.",
				  iface.name);

		}
	}

	return 0;
}
