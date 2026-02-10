Address_Scan_Init(void)
{
    int num_interfaces = 0;
    int fd;


    ifc.ifc_len = 0;
    SNMP_FREE(ifc.ifc_buf);
    ifr_counter = 0;

    do
    {
	if ((fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
	{
	    DEBUGMSGTL(("snmpd", "socket open failure in Address_Scan_Init\n"));
	    return;
	}
	num_interfaces += 16;

	ifc.ifc_len = sizeof(struct ifreq) * num_interfaces;
	ifc.ifc_buf = (char*) realloc(ifc.ifc_buf, ifc.ifc_len);

	    if (ioctl(fd, SIOCGIFCONF, &ifc) < 0)
	    {
		ifr=NULL;
		close(fd);
	   	return;
	    }
	    close(fd);
    }
    while (ifc.ifc_len >= (sizeof(struct ifreq) * num_interfaces));

    ifr = ifc.ifc_req;
    close(fd);
}
