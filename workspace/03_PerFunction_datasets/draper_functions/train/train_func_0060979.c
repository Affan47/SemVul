dicod_add_command(struct dicod_command *cmd)
{
    if (!command_list) {
	command_list = xdico_list_create();
	dico_list_set_comparator(command_list, _cmd_arg_cmp);
    }
    xdico_list_append(command_list, cmd);
}
