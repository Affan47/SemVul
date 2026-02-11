main(int argc, char *argv[])
{
	comedi_t *dev;
	comedi_cmd cmd;
	int ret;
	struct parsed_options options;

	init_parsed_options(&options);
	options.channel = -1;
	parse_options(&options, argc, argv);

	dev = comedi_open(options.filename);
	if(!dev){
		perror(options.filename);
		exit(1);
	}
	device = dev;

	if(options.channel >= 0) pin_data = options.channel;

	ret = fcntl(comedi_fileno(dev),F_SETFL,O_NONBLOCK);
	if(ret<0)perror("fcntl");

	prepare_cmd(dev, &cmd, options.subdevice);

	do_cmd(dev,&cmd);

	return 0;
}
