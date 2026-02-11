ibft_check_initiator_for(void *data, int type)
{
	struct ibft_kobject *entry = data;
	struct ibft_initiator *init = entry->initiator;
	umode_t rc = 0;

	switch (type) {
	case ISCSI_BOOT_INI_INDEX:
	case ISCSI_BOOT_INI_FLAGS:
		rc = S_IRUGO;
		break;
	case ISCSI_BOOT_INI_ISNS_SERVER:
		if (address_not_null(init->isns_server))
			rc = S_IRUGO;
		break;
	case ISCSI_BOOT_INI_SLP_SERVER:
		if (address_not_null(init->slp_server))
			rc = S_IRUGO;
		break;
	case ISCSI_BOOT_INI_PRI_RADIUS_SERVER:
		if (address_not_null(init->pri_radius_server))
			rc = S_IRUGO;
		break;
	case ISCSI_BOOT_INI_SEC_RADIUS_SERVER:
		if (address_not_null(init->sec_radius_server))
			rc = S_IRUGO;
		break;
	case ISCSI_BOOT_INI_INITIATOR_NAME:
		if (init->initiator_name_len)
			rc = S_IRUGO;
		break;
	default:
		break;
	}

	return rc;
}
