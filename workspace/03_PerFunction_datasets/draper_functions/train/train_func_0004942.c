cmd_obey()
{
	CMD_REQUIRE_ARGS(1);

	for (int i=0; commands[i].name != NULL; i++) {
		if (cmd_args[1] != commands[i].name)
			continue;

		commands[i].ignore = false;
		if (!xboard) {
			printf("Won't ignore command '%s' anymore.\n",
					cmd_args[1].c_str());
		}
		return;
	}

	printf("Error (unknown command): %s\n", cmd_args[1].c_str());
}
