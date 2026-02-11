main(int argc, char *argv[])
{
	struct sigaction sa;
	int ret;
	sigset_t sigset;
	int flags;
	struct parsed_options options;

	init_parsed_options(&options);
	parse_options(&options, argc, argv);

	device = comedi_open(options.filename);
	if(!device){
		perror(options.filename);
		exit(1);
	}

	out_subd = 2;

	config_output();

	fcntl(comedi_fileno(device), F_SETOWN, getpid());
	flags = fcntl(comedi_fileno(device),F_GETFL);
	ret = fcntl(comedi_fileno(device),F_SETFL,flags|O_ASYNC);

	if(ret<0)perror("fcntl");

	memset(&sa,0,sizeof(sa));
	sa.sa_handler = &sigio_handler;
	ret = sigaction(SIGIO,&sa,NULL);
	if(ret<0)perror("sigaction");

	sigemptyset(&sigset);
	sigaddset(&sigset,SIGIO);
	ret = sigprocmask(SIG_UNBLOCK,&sigset,NULL);
	if(ret<0)perror("sigprocmask");

#if 0
	{
	struct sched_param p;
	memset(&p,0,sizeof(p));
	p.sched_priority = 1;
	ret = sched_setscheduler(0,SCHED_FIFO,&p);
	if(ret<0)perror("sched_setscheduler");
	}
#endif

	do_cmd_1(device, options.subdevice);

	return 0;
}
