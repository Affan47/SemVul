send_admin(const std::string &server)
{
	std::vector<std::string> params;
	if (!server.empty()) params.push_back(server);
	send_command("", "ADMIN", params);
}
