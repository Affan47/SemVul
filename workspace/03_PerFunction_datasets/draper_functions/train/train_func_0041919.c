ipmi_print_get_power_consmpt_data(struct ipmi_intf * intf, uint8_t unit)
{
	int rc = 0;
	IPMI_INST_POWER_CONSUMPTION_DATA instpowerconsumptiondata = {0,0,0,0};
	printf("\nPower consumption information\n");
	rc = ipmi_get_power_consumption_data(intf, unit);
	if (rc == (-1)) {
		return rc;
	}
	rc = ipmi_get_instan_power_consmpt_data(intf, &instpowerconsumptiondata);
	if (rc == (-1)) {
		return rc;
	}
	ipmi_print_get_instan_power_Amps_data(instpowerconsumptiondata);
	rc = ipmi_get_power_headroom_command(intf, unit);
	if (rc == (-1)) {
		return rc;
	}
	return rc;
}
