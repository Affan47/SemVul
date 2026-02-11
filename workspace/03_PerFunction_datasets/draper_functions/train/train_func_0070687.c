nutscan_add_option_to_device(nutscan_device_t * device,char * option, char * value)
{
	nutscan_options_t * opt;

	opt = &(device->opt);

	if( opt->option != NULL ) {
		while( opt->next != NULL ) {
			opt = opt->next;
		}

		opt->next = malloc(sizeof(nutscan_options_t));
		opt = opt->next;
		memset(opt,0,sizeof(nutscan_options_t));
	}

	if( option != NULL ) {
		opt->option = strdup(option);
	}
	else {
		opt->option = NULL;
	}

	if( value != NULL ) {
		opt->value = strdup(value);
	}
	else {
		opt->value = NULL;
	}
}
