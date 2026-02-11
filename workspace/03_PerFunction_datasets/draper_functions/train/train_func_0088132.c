setArgs(int argc, char* argv[])
{
	_command = argv[0];
	_pConfig->setInt("application.argc", argc);
	_args.reserve(argc);
	std::string argvKey = "application.argv[";
	for (int i = 0; i < argc; ++i)
	{
		std::string arg(argv[i]);
		_pConfig->setString(argvKey + NumberFormatter::format(i) + "]", arg);
		_args.push_back(arg);
	}
}
