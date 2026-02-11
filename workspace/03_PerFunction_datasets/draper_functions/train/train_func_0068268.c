cx_is_CalxedaSoc(struct ipmi_intf * intf, tboolean to_print)
{
	struct oem_device_info_basic_s {
		uint32_t iana;
		uint8_t parameter_revision;
		uint8_t major_ver;
		uint8_t minor_ver;
		uint8_t revision;
		uint32_t build_number;
		uint32_t timestamp;
		char firmware_ver[32];
	} __attribute__ ((packed));
	typedef struct oem_device_info_basic_s oem_device_info_basic_t;

	tboolean is_Calxeda_soc = 0;
	int rv = 0;
	uint8_t rs_data[MAX_MSG_DATA_SIZE];
	int rs_data_size = MAX_MSG_DATA_SIZE;
	uint8_t completion_code;
	oem_device_info_basic_t *basic_rs;

	basic_rs = (void *)rs_data;

	rs_data[0] = 0x01;
	rv = cx_send_ipmi_cmd(intf, IPMI_NETFN_OEM_SS,
			      IPMI_CMD_OEM_GET_DEVICE_INFO, rs_data, 1, rs_data,
			      &rs_data_size, &completion_code);
	if (rv == 0) {
		if (completion_code) {
			printf("command failed with 0x%X completion code\n",
			       completion_code & 0xFF);
		} else {
			time_t lt;
			if (0x96CD == basic_rs->iana) {
				is_Calxeda_soc = 1;
				if (to_print) {
					printf("Calxeda SoC (0x%6.6X)\n",
					       basic_rs->iana);
					printf("  Firmware Version: %s\n",
					       basic_rs->firmware_ver);
					printf("  SoC Version: %d.%d.%d\n",
					       basic_rs->major_ver,
					       basic_rs->minor_ver,
					       basic_rs->revision);
					printf("  Build Number: %X %s\n",
					       basic_rs->build_number,
					       ((basic_rs->
						 build_number & 0x0F) ==
						0x0D) ? "(Dirty)" : "");
					lt = basic_rs->timestamp;
					printf("  Timestamp (%d): %s\n",
					       basic_rs->timestamp,
					       asctime(localtime(&lt)));
				}
			} else {
				printf("This is not Calxeda SoC\n");
			}
		}
	}
	return is_Calxeda_soc;
}
