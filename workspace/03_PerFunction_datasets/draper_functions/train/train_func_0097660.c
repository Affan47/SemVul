send_notice_ctcp(const std::string &nickname, const std::string &command, const std::string &data)
{
	std::string line = data.empty() ? command : command + std::string(" ") + data;


	std::string::size_type pos;

	pos = 0;
	while (pos != std::string::npos)
	{
		pos = line.find('\\', pos);
		if (pos == std::string::npos) break;
		line.replace( pos, 1, "\\\\" );
		pos++;
	}

	pos = 0;
	while (pos != std::string::npos)
	{
		pos = line.find('\001', pos);
		if (pos == std::string::npos) break;
		line.replace( pos, 1, "\\a" );
		pos++;
	}

	std::string ctcp = std::string("\001") + line + std::string("\001");

	std::vector<std::string> params;
	params.push_back(nickname);
	params.push_back(ctcp);
	send_command("", "NOTICE", params);
}
