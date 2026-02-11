beiscsi_set_ipv6(struct Scsi_Host *shost,
		struct iscsi_iface_param_info *iface_param,
		void *data, uint32_t dt_len)
{
	struct beiscsi_hba *phba = iscsi_host_priv(shost);
	int ret = 0;

	switch (iface_param->param) {
	case ISCSI_NET_PARAM_IFACE_ENABLE:
		if (iface_param->value[0] == ISCSI_IFACE_ENABLE)
			ret = beiscsi_create_ipv6_iface(phba);
		else {
			iscsi_destroy_iface(phba->ipv6_iface);
			ret = 0;
		}
		break;
	case ISCSI_NET_PARAM_IPV6_ADDR:
		ret = mgmt_set_ip(phba, iface_param, NULL,
				  ISCSI_BOOTPROTO_STATIC);
		break;
	default:
		beiscsi_log(phba, KERN_ERR, BEISCSI_LOG_CONFIG,
			    "BS_%d : Param %d not supported\n",
			    iface_param->param);
	}

	return ret;
}
