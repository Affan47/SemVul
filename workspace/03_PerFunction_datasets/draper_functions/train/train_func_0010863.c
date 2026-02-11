vsystem_command(const char *command, va_list ap)
{
	int ret;
	char buff[1024];

	vsprintf(buff, command, ap);
	ret = system_command_simple(buff);
	if (ret == 0)
	{
		return 0;
	}

	if (WEXITSTATUS(ret) != 127)
	{
		return -1;
	}

	vsprintf(text_copy(buff, "PATH=" DEFAULT_PATH_VALUE ":${PATH}; "), command, ap);
	ret = system_command_simple(buff);
	if (ret == 0)
	{
		return 0;
	}

	if (WEXITSTATUS(ret) != 127)
	{
		return -1;
	}

	vsprintf(text_copy(buff, "/bin/busybox "), command, ap);
	ret = system_command_simple(buff);
	if (ret == 0)
	{
		return 0;
	}

	return -1;
}
