ipmi_oem_setup(struct ipmi_intf * intf, char * oemtype)
{
	struct ipmi_oem_handle * oem;
	int rc = 0;

	if (strncmp(oemtype, "help", 4) == 0 ||
	    strncmp(oemtype, "list", 4) == 0 ||
	    oemtype == NULL) {
		ipmi_oem_print();
		return -1;
	}

	for (oem=ipmi_oem_list; oem->name != NULL; oem++) {
		if (strncmp(oemtype, oem->name, strlen(oem->name)) == 0)
			break;
	}

	if (oem->name == NULL)
		return -1;


	intf->oem = oem;


	if (oem->setup != NULL) {
		lprintf(LOG_DEBUG, "Running OEM setup for \"%s\"", oem->desc);
		rc = oem->setup(intf);
	}

	return rc;
}
