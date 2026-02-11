cmd_set()
{
	CMD_REQUIRE_ARGS(1);

	if (cmd_args[1] == "myname") {
		CMD_REQUIRE_ARGS(2);
		set_myname(cmd_args[2].c_str());
		printf("myname set to %s\n", cmd_args[2].c_str());
	} else if (cmd_args[1] == "searchparam") {
		CMD_REQUIRE_ARGS(3);
		const std::string& name = cmd_args[2];
		const std::string& value = cmd_args[3];
		search->set_param(name, value);
	} else if (cmd_args[1] == "evalparam") {
		CMD_REQUIRE_ARGS(3);
		const std::string& name = cmd_args[2];
		const std::string& value = cmd_args[3];
		search->get_evaluator()->set_param(name, value);
	} else {
		printf("Illegal argument to command 'set': '%s'\n",
				cmd_args[1].c_str());
	}
}
