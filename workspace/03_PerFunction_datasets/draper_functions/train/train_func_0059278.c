sysinfo_param(const char *str, int *maxset)
{
	if (!str || !maxset)
		return (-1);

	*maxset = 4;
	if (!strcmp(str, "system_name"))
		return IPMI_SYSINFO_HOSTNAME;
	else if (!strcmp(str, "primary_os_name"))
		return IPMI_SYSINFO_PRIMARY_OS_NAME;
	else if (!strcmp(str, "os_name"))
		return IPMI_SYSINFO_OS_NAME;
	else if (!strcmp(str, "delloem_os_version"))
		return IPMI_SYSINFO_DELL_OS_VERSION;
	else if (!strcmp(str, "delloem_url")) {
		*maxset = 2;
		return IPMI_SYSINFO_DELL_URL;
	}

	return (-1);
}
