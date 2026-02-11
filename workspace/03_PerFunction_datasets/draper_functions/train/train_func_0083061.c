prepare_library(nic_t *nic)
{
	int rc;
	NIC_LIBRARY_EXIST_T exist;

	nic_fill_name(nic);


	if (nic->library_name != NULL) {

		exist = does_nic_library_exist(nic->library_name);
		if (exist == NIC_LIBRARY_DOESNT_EXIST) {
			LOG_ERR(PFX "NIC library doesn't exists: %s",
				nic->library_name);
			goto error;
		}
	}


	rc = find_set_nic_lib(nic);
	if (rc != 0) {
		LOG_ERR(PFX "%s: Couldn't find NIC library", nic->log_name);
		goto error;
	}

	LOG_INFO("%s: found NIC '%s'", nic->log_name, nic->pci_id->device_name);
error:
	return;
}
