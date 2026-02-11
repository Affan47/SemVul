main(const std::vector<std::string>& args)
	{
		if (!_helpRequested)
		{
			for (std::vector<std::string>::const_iterator it = args.begin(); it != args.end(); ++it)
			{
				convert(*it);
			}
		}
		return Application::EXIT_OK;
	}
