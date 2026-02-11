ipmi_rawspd_main(struct ipmi_intf * intf, int argc, char ** argv)
{
	struct ipmi_rs *rsp;
	uint8_t msize = IPMI_I2C_MASTER_MAX_SIZE;
	uint8_t channel = 0;
	uint8_t i2cbus = 0;
	uint8_t i2caddr = 0;
	uint8_t spd_data[RAW_SPD_SIZE];
	int i;

	memset(spd_data, 0, RAW_SPD_SIZE);

	if (argc < 2 || strncmp(argv[0], "help", 4) == 0) {
		lprintf(LOG_NOTICE, "usage: spd <i2cbus> <i2caddr> [channel] [maxread]");
		return 0;
	}

	i2cbus  =  (uint8_t)strtoul(argv[0], NULL, 0);
	i2caddr =  (uint8_t)strtoul(argv[1], NULL, 0);
	if( argc >= 3 ){
		channel	= (uint8_t)strtoul(argv[2], NULL, 0);
	}
	if( argc >= 4 ){
		msize	  =  (uint8_t)strtoul(argv[3], NULL, 0);
	}

	i2cbus = ((channel & 0xF) << 4) | ((i2cbus & 7) << 1) | 1;

	for (i = 0; i < RAW_SPD_SIZE; i+= msize) {
		rsp = ipmi_master_write_read(intf, i2cbus, i2caddr,
					     (uint8_t *)&i, 1, msize );
		if (rsp == NULL) {
			lprintf(LOG_ERR, "Unable to perform I2C Master Write-Read");
			return -1;
		}

		memcpy(spd_data+i, rsp->data, msize);
	}

	ipmi_spd_print(spd_data, i);
	return 0;
}
