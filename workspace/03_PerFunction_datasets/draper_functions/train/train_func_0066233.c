gpg_get_uid (const std::string& fingerprint)
{

	std::vector<std::string>	command;
	command.push_back("gpg");
	command.push_back("--batch");
	command.push_back("--with-colons");
	command.push_back("--fixed-list-mode");
	command.push_back("--list-keys");
	command.push_back("0x" + fingerprint);
	std::stringstream		command_output;
	if (!successful_exit(exec_command(command, command_output))) {

		return "";
	}

	while (command_output.peek() != -1) {
		std::string		line;
		std::getline(command_output, line);
		if (line.substr(0, 4) == "uid:") {


			return gpg_nth_column(line, 9);
		}
	}

	return "";
}
