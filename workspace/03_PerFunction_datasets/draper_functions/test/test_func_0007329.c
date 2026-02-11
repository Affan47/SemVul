parse_args(int argc, char **argv, struct slogic_handle *handle)
{
	int c;
	int libusb_debug_level = 0;
	char *endptr;
        opterr = 0;

	while ((c = getopt(argc, argv, "n:f:r:hb:t:o:u:")) != -1) {
		switch (c) {
		case 'n':
			n_samples = strtol(optarg, &endptr, 10);
			if (*endptr != '\0' || n_samples <= 0) {
				short_usage("Invalid number of samples, must be a positive integer: %s", optarg);
				return false;
			}
			break;
		case 'f':
			output_file_name = optarg;
			break;
		case 'r':
			sample_rate = slogic_parse_sample_rate(optarg);
			if (!sample_rate) {
				short_usage("Invalid sample rate: %s", optarg);
				return false;
			}
			break;
		case 'h':
			full_usage();
			return false;
		case 'b':
			handle->transfer_buffer_size = strtol(optarg, &endptr, 10);
			if (*endptr != '\0' || handle->transfer_buffer_size <= 0) {
				short_usage("Invalid transfer buffer size, must be a positive integer: %s", optarg);
				return false;
			}
			break;
		case 't':
			handle->n_transfer_buffers = strtol(optarg, &endptr, 10);
			if (*endptr != '\0' || handle->n_transfer_buffers <= 0) {
				short_usage("Invalid transfer buffer count, must be a positive integer: %s", optarg);
				return false;
			}
			break;
		case 'o':
			handle->transfer_timeout = strtol(optarg, &endptr, 10);
			if (*endptr != '\0' || handle->transfer_timeout <= 0) {
				short_usage("Invalid transfer timeout, must be a positive integer: %s", optarg);
				return false;
			}
			break;
		case 'u':
			libusb_debug_level = strtol(optarg, &endptr, 10);
			if (*endptr != '\0' || libusb_debug_level < 0 || libusb_debug_level > 3) {
				short_usage("Invalid libusb debug level, must be a positive integer between "
					    "0 and 3: %s", optarg);
				return false;
			}
			libusb_set_debug(handle->context, libusb_debug_level);
			break;

		default:
			short_usage("Something is wrong. Use %s -h for usage.", c, me);
			return false;
		case '?':
			short_usage("Unknown argument: %c. Use %s -h for usage.", optopt, me);
			return false;
		}
	}

	if (!output_file_name) {
		short_usage("An output file has to be specified.", optarg);
		return false;
	}

	if (!sample_rate) {
		short_usage("A sample rate has to be specified.", optarg);
		return false;
	}

	if (!n_samples) {
		n_samples = sample_rate->samples_per_second;
	}

	return true;
}
