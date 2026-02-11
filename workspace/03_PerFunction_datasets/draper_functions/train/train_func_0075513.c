ips_setup(char *ips_str)
{

	int i;
	char *key;
	char *value;
	IPS_OPTION options[] = {
		{"noi2o", &ips_force_i2o, 0},
		{"nommap", &ips_force_memio, 0},
		{"ioctlsize", &ips_ioctlsize, IPS_IOCTL_SIZE},
		{"cdboot", &ips_cd_boot, 0},
		{"maxcmds", &MaxLiteCmds, 32},
	};


	while ((key = strsep(&ips_str, ",."))) {
		if (!*key)
			continue;
		value = strchr(key, ':');
		if (value)
			*value++ = '\0';


		for (i = 0; i < ARRAY_SIZE(options); i++) {
			if (strncasecmp
			    (key, options[i].option_name,
			     strlen(options[i].option_name)) == 0) {
				if (value)
					*options[i].option_flag =
					    simple_strtoul(value, NULL, 0);
				else
					*options[i].option_flag =
					    options[i].option_value;
				break;
			}
		}
	}

	return (1);
}
