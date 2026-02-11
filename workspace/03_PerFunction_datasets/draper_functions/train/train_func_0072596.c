cx_feature_main(struct ipmi_intf *intf, int argc, char **argv)
{
	uint8_t rs_data[MAX_MSG_DATA_SIZE];
	int rs_data_size = MAX_MSG_DATA_SIZE;
	int rq_data_size = 0;
	uint8_t *rq_data;
	uint8_t completion_code;
	int get_op = 0;
	const struct valstr oem_features[] = {
		{0x01, "selaging"},
		{0x02, "hwwd"},
		{0x03, "tps"},
		{0x00, "Invalid"},
	};
	int rv = 0;
	int i;
	int feature_index = 0;

	if (argc < 2 || strncmp(argv[0], "help", 4) == 0) {
		cx_feature_usage();
		return 0;
	}

	rq_data = rs_data;
	if (strncmp(argv[0], "status", 6) == 0) {
		rq_data_size = 2;
		rq_data[0] = 2;
		get_op = 1;
	} else if (strncmp(argv[0], "enable", 6) == 0) {
		rq_data[2] = 1;
		rq_data_size = 3;
		rq_data[0] = 1;
	} else if (strncmp(argv[0], "disable", 7) == 0) {
		rq_data[2] = 0;
		rq_data_size = 3;
		rq_data[0] = 1;
	} else {
		rv = -1;
	}

	if (0 == rv) {
		i = 0;
		rv = -1;
		while (oem_features[i].val) {
			if (strncmp
			    (argv[1], oem_features[i].str,
			     strlen(oem_features[i].str)) == 0) {
				rq_data[1] = oem_features[i].val;
				rv = 0;
				feature_index = i;
				break;
			}
			i++;
		}
	}


	if (0 == rv) {

		rv = cx_send_ipmi_cmd(intf, IPMI_NETFN_OEM_SS,
				      IPMI_CMD_OEM_FEATURES_ENABLE, rq_data,
				      rq_data_size, rs_data, &rs_data_size,
				      &completion_code);
		if (0 == rv) {
			if (get_op) {
				if (2 == feature_index) {
					printf("   %s state is %d %s\n", oem_features[feature_index].str,
						   rs_data[0], tps_to_string(rs_data[0]));
				} else {
					printf("   %s is %s\n",
						   oem_features[feature_index].str,
						   rs_data[0] ? "enabled" : "disabled");
				}
			}
		}
	}

	if (rv) {
		cx_feature_usage();
	}

	return rv;
}
