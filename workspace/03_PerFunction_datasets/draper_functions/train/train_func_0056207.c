CheckLCDSupport(struct ipmi_intf * intf)
{
	int rc;
	LcdSupported = 0;
	rc = ipmi_mc_getsysinfo(intf, IPMI_DELL_LCD_STATUS_SELECTOR, 0, 0, 0, NULL);
	if (rc == 0) {
		LcdSupported = 1;
	}
}
