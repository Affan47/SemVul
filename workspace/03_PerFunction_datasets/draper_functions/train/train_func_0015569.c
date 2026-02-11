main(int argc, char* argv[])
{
  try
  {
    cxxtools::Arg<bool> fatal;
    fatal.set(argc, argv, 'f');
    fatal.set(argc, argv, "--fatal");

    cxxtools::Arg<bool> error;
    error.set(argc, argv, 'e');
    error.set(argc, argv, "--error");

    cxxtools::Arg<bool> warn;
    warn.set(argc, argv, 'w');
    warn.set(argc, argv, "--warn");

    cxxtools::Arg<bool> info;
    info.set(argc, argv, 'i');
    info.set(argc, argv, "--info");

    cxxtools::Arg<bool> debug;
    debug.set(argc, argv, 'd');
    debug.set(argc, argv, "--debug");

    cxxtools::Arg<std::string> properties("log4j.properties");
    properties.set(argc, argv, 'p');
    properties.set(argc, argv, "--properties");

    if (argc <= 2)
    {
      std::cerr << "usage: " << argv[0] << " [options] category message\n"
                   "\toptions:  -f|--fatal\n"
                   "\t          -e|--error\n"
                   "\t          -w|--warn\n"
                   "\t          -i|--info\n"
                   "\t          -d|--debug\n"
                   "\t          -p|--properties filename" << std::endl;
      return -1;
    }

    log_init(properties.getValue());

    category = argv[1];

    for (int a = 2; a < argc; ++a)
    {
      if (fatal)
        log_fatal(argv[a]);
      else if (error)
        log_error(argv[a]);
      else if (warn)
        log_warn(argv[a]);
      else if (info)
        log_info(argv[a]);
      else if (debug)
        log_debug(argv[a]);
    }
  }
  catch (const std::exception& e)
  {
    std::cerr << e.what() << std::endl;
    return -1;
  }
}
