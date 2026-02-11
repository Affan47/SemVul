ipmi_lcd_configure(struct ipmi_intf * intf, int command,
		int8_t line_number, char * text)
{
	int rc = 0;
	if (IPMI_DELL_LCD_CONFIG_USER_DEFINED == command) {
		rc = ipmi_lcd_set_text(intf, text, line_number);
	}
	if (rc == 0) {
		rc = ipmi_lcd_set_configure_command(intf, command);
	}
	return rc;
}
