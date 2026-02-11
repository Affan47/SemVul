parse_options (int argc, char *argv[])
{
  int opt;

  static const char helpText[] =
    "Usage: %s [OPTION...]\n"
    "  -d, --debug=INT                 Set debugging to LEVEL\n"
    "  -i, --cdrom-device[=DEVICE]     show only info about CD-ROM device\n"
    "  -q, --quiet                     Don't produce warning output\n"
    "  -V, --version                   display version and copyright information\n"
    "                                  and exit\n"
    "\n"
    "Help options:\n"
    "  -?, --help                      Show this help message\n"
    "  --usage                         Display brief usage message\n";

  static const char usageText[] =
    "Usage: %s [-d|--debug INT] [-i|--cdrom-device DEVICE] [-q|--quiet]\n"
    "        [-V|--version] [-?|--help] [--usage]\n";

  static const char optionsString[] = "d:i::qV?";
  static const struct option optionsTable[] = {
    {"debug", required_argument, NULL, 'd' },
    {"cdrom-device", optional_argument, NULL, 'i' },
    {"quiet", no_argument, NULL, 'q' },
    {"version", no_argument, NULL, 'V' },
    {"help", no_argument, NULL, '?' },
    {"usage", no_argument, NULL, OP_USAGE },
    {NULL, 0, NULL, 0 }
  };

  program_name = strrchr(argv[0],'/');
  program_name = program_name ? strdup(program_name+1) : strdup(argv[0]);

  while ((opt = getopt_long(argc, argv, optionsString, optionsTable, NULL)) != -1) {
    switch (opt) {
    case 'd':
      opts.debug_level = atoi(optarg);
      break;

    case 'i':
      if (opts.source_image != (source_image_t) DRIVER_UNKNOWN) {


	report( stderr, "%s: another source type option given before.\n",
		program_name );
	report( stderr, "%s: give only one source type option.\n",
		program_name );
	break;
      } else {
	opts.source_image  = DRIVER_DEVICE;
	if (optarg != NULL) {
	  source_name = fillout_device_name(optarg);
	}
	break;
      }
      break;

    case 'q':
      opts.silent = 1;
      break;

    case 'V':
      opts.version_only = 1;
      break;

    case '?':
      fprintf(stdout, helpText, program_name);
      free(program_name);
      exit(EXIT_INFO);
      break;

    case OP_USAGE:
      fprintf(stderr, usageText, program_name);
      free(program_name);
      exit(EXIT_FAILURE);
      break;

    case OP_HANDLED:
      break;

    default:
      return false;
    }
  }
  if (optind < argc) {
    const char *remaining_arg = argv[optind++];


    if (source_name != NULL) {
      report( stderr, "%s: Source specified in option %s and as %s\n",
	      program_name, source_name, remaining_arg);
      free(program_name);
      exit (EXIT_FAILURE);
    }

    if (opts.source_image == (source_image_t) DRIVER_DEVICE)
      source_name = fillout_device_name(remaining_arg);
    else
      source_name = strdup(remaining_arg);

    if (optind < argc) {
      report( stderr, "%s: Source specified in previously %s and %s\n",
	      program_name, source_name, remaining_arg);
      free(program_name);
      exit (EXIT_FAILURE);
    }
  }

  return true;
}
