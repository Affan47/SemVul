bfa_fcs_fabric_psymb_init(struct bfa_fcs_fabric_s *fabric)
{
	struct bfa_lport_cfg_s *port_cfg = &fabric->bport.port_cfg;
	char model[BFA_ADAPTER_MODEL_NAME_LEN] = {0};
	struct bfa_fcs_driver_info_s *driver_info = &fabric->fcs->driver_info;

	bfa_ioc_get_adapter_model(&fabric->fcs->bfa->ioc, model);


	strncpy((char *)&port_cfg->sym_name, model,
		BFA_FCS_PORT_SYMBNAME_MODEL_SZ);
	strncat((char *)&port_cfg->sym_name, BFA_FCS_PORT_SYMBNAME_SEPARATOR,
		sizeof(BFA_FCS_PORT_SYMBNAME_SEPARATOR));


	strncat((char *)&port_cfg->sym_name, (char *)driver_info->version,
		BFA_FCS_PORT_SYMBNAME_VERSION_SZ);
	strncat((char *)&port_cfg->sym_name, BFA_FCS_PORT_SYMBNAME_SEPARATOR,
		sizeof(BFA_FCS_PORT_SYMBNAME_SEPARATOR));


	strncat((char *)&port_cfg->sym_name,
		(char *)driver_info->host_machine_name,
		BFA_FCS_PORT_SYMBNAME_MACHINENAME_SZ);
	strncat((char *)&port_cfg->sym_name, BFA_FCS_PORT_SYMBNAME_SEPARATOR,
		sizeof(BFA_FCS_PORT_SYMBNAME_SEPARATOR));


	if (driver_info->host_os_patch[0] == '\0') {
		strncat((char *)&port_cfg->sym_name,
			(char *)driver_info->host_os_name,
			BFA_FCS_OS_STR_LEN);
		strncat((char *)&port_cfg->sym_name,
			BFA_FCS_PORT_SYMBNAME_SEPARATOR,
			sizeof(BFA_FCS_PORT_SYMBNAME_SEPARATOR));
	} else {
		strncat((char *)&port_cfg->sym_name,
			(char *)driver_info->host_os_name,
			BFA_FCS_PORT_SYMBNAME_OSINFO_SZ);
		strncat((char *)&port_cfg->sym_name,
			BFA_FCS_PORT_SYMBNAME_SEPARATOR,
			sizeof(BFA_FCS_PORT_SYMBNAME_SEPARATOR));


		strncat((char *)&port_cfg->sym_name,
			(char *)driver_info->host_os_patch,
			BFA_FCS_PORT_SYMBNAME_OSPATCH_SZ);
	}


	port_cfg->sym_name.symname[BFA_SYMNAME_MAXLEN - 1] = 0;
}
