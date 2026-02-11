main(int argc, char *argv[])
{
	unsigned period_ns;
	int retval;
	lsampl_t routing;
	struct parsed_options options;

	init_parsed_options(&options);
	options.freq = 0.;
	parse_options(&options, argc, argv);

	device = comedi_open(options.filename);
	if(!device){
		comedi_perror(options.filename);
		exit(-1);
	}
	if(options.freq > 0.)
		period_ns = 1e9 / options.freq;
	else
		period_ns = 0;
	routing = options.value;
	printf("Selecting routing %d for channel %d on subdevice %d.\n", routing, options.channel, options.subdevice);

	retval = comedi_set_routing(device, options.subdevice, options.channel, routing);
	if(retval < 0) comedi_perror("comedi_do_insn");
	return retval;
}
