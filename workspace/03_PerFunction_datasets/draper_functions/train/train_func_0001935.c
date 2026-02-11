init_command_data()
{
	int cmd_counter;
	int i;
	extern int map(char ch);

	for (cmd_counter = 0; cmd_counter < CMD_NUM; cmd_counter++)
	{
		command_list[cmd_counter].head = command_head[cmd_counter];
		command_list[cmd_counter].doit = NULL;
	}

	for (i = 0; i < USED_CHAR_NUM; i++)
		command_index[i] = -1;
	for (i = 0; i < CMD_NUM; i++)
	{
		if (-1 == command_index[map(command_list[i].head[0])])
			command_index[map(command_list[i].head[0])] = i;
	}

	command_list[QUIT].doit = quit_;
	command_list[LED].doit = led_;
}
