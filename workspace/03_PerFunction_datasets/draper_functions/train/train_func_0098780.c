ipmi_lcd_get_info_wh(struct ipmi_intf * intf)
{
	IPMI_DELL_LCD_CAPS lcd_caps;
	char lcdstring[IPMI_DELL_LCD_STRING_LENGTH_MAX+1] = {0};
	int rc;
	printf("LCD info\n");
	if (ipmi_lcd_get_configure_command_wh(intf) != 0) {
		return -1;
	}
	if (lcd_mode.lcdmode== IPMI_DELL_LCD_CONFIG_DEFAULT) {
		char text[IPMI_DELL_LCD_STRING_LENGTH_MAX+1] = {0};
		if (ipmi_lcd_get_platform_model_name(intf, text,
					IPMI_DELL_LCD_STRING_LENGTH_MAX,
					IPMI_DELL_PLATFORM_MODEL_NAME_SELECTOR) != 0) {
			return (-1);
		}
		printf("    Setting:Model name\n");
		printf("    Line 1:  %s\n", text);
	} else if (lcd_mode.lcdmode == IPMI_DELL_LCD_CONFIG_NONE) {
		printf("    Setting:   none\n");
	} else if (lcd_mode.lcdmode == IPMI_DELL_LCD_CONFIG_USER_DEFINED) {
		printf("    Setting: User defined\n");
		rc = ipmi_mc_getsysinfo(intf, IPMI_DELL_LCD_GET_CAPS_SELECTOR, 0, 0,
				sizeof(lcd_caps), &lcd_caps);
		if (rc < 0) {
			lprintf(LOG_ERR, "Error getting LCD capabilities.");
			return -1;
		} else if ((rc == 0xc1) || (rc == 0xcb)) {
			lprintf(LOG_ERR, "Error getting LCD capabilities: "
					"Command not supported on this system.");
		} else if (rc > 0) {
			lprintf(LOG_ERR, "Error getting LCD capabilities: %s",
					val2str(rc, completion_code_vals));
			return -1;
		}
		if (lcd_caps.number_lines > 0) {
			memset(lcdstring, 0, IPMI_DELL_LCD_STRING_LENGTH_MAX + 1);
			rc = ipmi_lcd_get_single_line_text(intf, lcdstring,
					lcd_caps.max_chars[0]);
			printf("    Text:    %s\n", lcdstring);
		} else {
			printf("    No lines to show\n");
		}
	} else if (lcd_mode.lcdmode == IPMI_DELL_LCD_iDRAC_IPV4ADRESS) {
		printf("    Setting:   IPV4 Address\n");
	} else if (lcd_mode.lcdmode == IPMI_DELL_LCD_IDRAC_MAC_ADDRESS) {
		printf("    Setting:   MAC Address\n");
	} else if (lcd_mode.lcdmode == IPMI_DELL_LCD_OS_SYSTEM_NAME) {
		printf("    Setting:   OS System Name\n");
	} else if (lcd_mode.lcdmode == IPMI_DELL_LCD_SERVICE_TAG) {
		printf("    Setting:   System Tag\n");
	} else if (lcd_mode.lcdmode == IPMI_DELL_LCD_iDRAC_IPV6ADRESS) {
		printf("    Setting:  IPV6 Address\n");
	} else if (lcd_mode.lcdmode == IPMI_DELL_LCD_ASSET_TAG) {
		printf("    Setting:  Asset Tag\n");
	} else if (lcd_mode.lcdmode == IPMI_DELL_LCD_AMBEINT_TEMP) {
		printf("    Setting:  Ambient Temp\n");
		if (lcd_mode.lcdquallifier & 0x02) {
			printf("    Unit:  F\n");
		} else {
			printf("    Unit:  C\n");
		}
	} else if (lcd_mode.lcdmode == IPMI_DELL_LCD_SYSTEM_WATTS) {
		printf("    Setting:  System Watts\n");
		if (lcd_mode.lcdquallifier & 0x01) {
			printf("    Unit:  BTU/hr\n");
		} else {
			printf("    Unit:  Watt\n");
		}
	}
	if (lcd_mode.error_display == IPMI_DELL_LCD_ERROR_DISP_SEL) {
		printf("    Error Display:  SEL\n");
	} else if (lcd_mode.error_display == IPMI_DELL_LCD_ERROR_DISP_VERBOSE) {
		printf("    Error Display:  Simple\n");
	}
	return 0;
}
